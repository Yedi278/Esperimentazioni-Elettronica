/*
 * Custom_ADC.c
 *
 *      Author: yehan
 */
#include "Custom_ADC.h"


/* GLOBAL VARIABLES */
volatile bool pre_triggd = 0;
volatile bool triggd = 0;
volatile uint16_t trig_indx=0;
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

	/*	PRIMO ADC	*/

	/*	IN0 -> PIN PC2 o A4
	 * */
	ADCx_custom_init(ADC3, 0);

	/*	IN19 -> PIN PA5 o D13
	 * */
	ADCx_custom_init(ADC2, 15);


	// TIM6 set to 240Mhz
	TIM6->PSC = 12; // TIM6 CLOCK/PSC
	TIM6->ARR = 13;	// TIM6 CLOCK/PSC/ARR
	TIM6->CNT = 0;
	TIM6->DIER &= ~TIM_DIER_UIE;

	// 240 Mhz -> 20 Mhz -> 1 Mhz

	ADC3->IER |= ADC_IER_EOCIE;	// interrupt ADC
	ADC2->IER &= ~ADC_IER_EOCIE;
}



void ADC_custom_interrupt_pre(){

	TIM6->CR1 &= ~TIM_CR1_CEN;

	extern volatile bool pre_triggd;
	extern volatile bool triggd;

	if(triggd){

		if(DMA2_Stream0->NDTR == trig_indx){

			TIM6->CR1 &= ~TIM_CR1_CEN;
			ADC3->ISR |= ADC_ISR_EOC;

			triggd = false;

			USART3->CR3 |= USART_CR3_DMAT;
			return;
		}
		goto start_timer;

	}else{
		if(!pre_triggd){

			pre_triggd = !(COMP12->SR & COMP_SR_C2VAL) && !(COMP12->SR & COMP_SR_C1VAL);
			goto start_timer;

		}else if((COMP12->SR & COMP_SR_C2VAL) && !(COMP12->SR & COMP_SR_C1VAL)){

//			trig_indx = (DMA2_Stream0->NDTR + 100UL)% 1000UL + 1UL;
			trig_indx = DMA2_Stream0->NDTR;
			triggd = true;
			pre_triggd = false;
//			return;
			goto start_timer;
		}
	}

	start_timer:
	TIM6->CR1 |= TIM_CR1_CEN;
}

void ADC_custom_interrupt(){

	if (triggd && (DMA2_Stream0->NDTR == trig_indx)) {
	    TIM6->CR1 &= ~TIM_CR1_CEN;
	    ADC3->ISR |= ADC_ISR_EOC;
	    triggd = false;
	    USART3->CR3 |= USART_CR3_DMAT;
	    return;
	}

	if (!(COMP12->SR & COMP_SR_C2VAL)) {
	    if (!triggd) {
	        triggd = true;
	        trig_indx = DMA2_Stream0->NDTR;
	    }
	} else {
	    triggd = false;
	}
}










