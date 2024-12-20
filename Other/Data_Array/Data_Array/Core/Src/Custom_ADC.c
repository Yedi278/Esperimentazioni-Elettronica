/*
 * Custom_ADC.c
 *
 *      Author: yehan
 */
#include "Custom_ADC.h"
#include "Custom_dma.h"

/* GLOBAL VARIABLES */
volatile bool pre_triggd;
volatile bool triggd;
volatile uint16_t trig_indx;
volatile uint16_t n_data_index;
/* END OF GLOB VARIABLES */

void ADCx_custom_init(ADC_TypeDef *ADCx, uint8_t INx_Pin){

//	ADCx->CR &= ~ADC_CR_ADSTART;

	ADCx->SQR1 = 0; // per azzerare la configurazione dell'ide

	ADCx->SQR1 |= (0 << ADC_SQR1_L_Pos);	// Indico quanti canali leggere 0=1

	ADCx->SQR1 |= (INx_Pin << ADC_SQR1_SQ1_Pos);

	ADCx->PCSEL = 0;
	ADCx->PCSEL |= (1 << (ADC_PCSEL_PCSEL_Pos + INx_Pin)); // Dichiaro quali canali leggere : 18 e 19

	/* Calibrazione */
	ADCx->CR &= ~ADC_CR_ADCALDIF;   // Imposto misura single read;
	ADCx->CR |= ADC_CR_ADCALLIN;	// Calibrazione Lineare con offset
	ADCx->CR &= ~ADC_CR_ADEN;		// Occorre ADC spento
	ADCx->CR |= ADC_CR_ADCAL;		// Inizio calibrazione


	while((ADCx->CR & ADC_CR_ADCAL) != 0){};
	// FIne calibrazione

	ADCx->ISR |= ADC_ISR_ADRDY;		// Azzero il bit prima del controllo
	ADCx->CR |= ADC_CR_ADEN;		// Accendo l' ADC

	while((ADCx->ISR & ADC_ISR_ADRDY) != 0){}

	ADCx->ISR |= ADC_ISR_ADRDY;		// Azzero il Ready bit
	// Fine accensione

	/* ADR INIZIALIZZATO */
}


void ADC_custom_init(){

	pre_triggd=0;
	triggd=0;
	trig_indx=0;
	n_data_index=0;

	/*	IN0 -> PIN PC2 o A4
	 * */
	ADCx_custom_init(ADC3, 0);

	// TIM6 set to 240Mhz
	TIM6->PSC = 12; // TIM6 CLOCK/PSC
	TIM6->ARR = 7;	// TIM6 CLOCK/PSC/ARR
	TIM6->CNT = 0;
	TIM6->DIER &= ~TIM_DIER_UIE;

	// 240 Mhz -> 20 Mhz -> 1 Mhz

	ADC3->IER |= ADC_IER_EOCIE;	// interrupt ADC
}



void ADC_custom_interrupt(){

//	TIM6->CR1 &= ~TIM_CR1_CEN;

	if(triggd){

		if(DMA2_Stream0->NDTR == trig_indx){

			DMA_data_buffer[n_data_index][DMA_SINGLE_DATA_BUFF_SIZE-1] = (uint16_t)trig_indx;

			++n_data_index;
			if(n_data_index > DMA_N_DATA_SETS-1){

				TIM6->CR1 &= ~TIM_CR1_CEN;

				triggd = false;
				COMP2->CFGR &= ~COMP_CFGRx_EN;

				DMA2_Stream0->M0AR = (uint32_t)(&DMA_data_buffer[0][0]);

				n_data_index=0;
				DMA2_Stream1->NDTR = 2*DMA_N_DATA_SETS * DMA_SINGLE_DATA_BUFF_SIZE;
				DMA2_Stream1->CR |= DMA_SxCR_EN;
				return;
			}

			triggd = false;
			DMA2_Stream0->CR &= ~DMA_SxCR_EN;	// Spengo ADC
			DMA2_Stream0->M0AR = (uint32_t)(&DMA_data_buffer[n_data_index][0]);
			DMA2_Stream0->CR |= DMA_SxCR_EN;
		}

		return;
//		goto start_timer;

	}else if(!pre_triggd && (ADC3->DR < PRETRIG_VALUE)){

			pre_triggd = true;
			COMP2->CFGR |= COMP_CFGRx_EN;
			return;
//			goto start_timer;
	}

	start_timer:
//	TIM6->CR1 |= TIM_CR1_CEN;
	return;
}

void COMP_custom_interrupt(){


	if(pre_triggd){

		if((COMP12->SR & COMP_SR_C2VAL)){

			trig_indx = DMA2_Stream0->NDTR;
			pre_triggd = false;
			triggd = true;
			COMP2->CFGR &= ~COMP_CFGRx_EN;
			goto reset_COMP;
		}
	}

	reset_COMP:
		COMP12->ICFR &= ~COMP_ICFR_C2IF;

}







