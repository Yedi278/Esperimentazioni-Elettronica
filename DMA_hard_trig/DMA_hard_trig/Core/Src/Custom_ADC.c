/*
 * Custom_ADC.c
 *
 *  Created on: Oct 17, 2024
 *      Author: yehan
 */
#include "Custom_ADC.h"


/* GLOBAL VARIABLES */
volatile bool pre_triggd = 0;
volatile bool triggd = 0;
volatile uint16_t trig_indx=0;
/* END OF GLOB VARIABLES */


void ADC_custom_init(){


//	ADC3->CR &= ~ADC_CR_ADSTART;
	ADC3->SQR1=0; // per azzerare la configurazione dell'ide

	ADC3->SQR1 |= (0 << ADC_SQR1_L_Pos);	// Indico quanti canali leggere

	ADC3->SQR1 |= (0 << ADC_SQR1_SQ1_Pos);

	ADC3->PCSEL |= ADC_PCSEL_PCSEL_0; // Dichiaro quali canali leggere : 18 e 19


	/* Calibrazione */
	ADC3->CR &= ~ADC_CR_ADCALDIF;   // Imposto misura single read;
	ADC3->CR |= ADC_CR_ADCALLIN;	// Calibrazione Lineare con offset
	ADC3->CR &= ~ADC_CR_ADEN;		// Occorre ADC spento
	ADC3->CR |= ADC_CR_ADCAL;		// Inizio calibrazione


	while((ADC3->CR & ADC_CR_ADCAL) != 0){};
	// FIne calibrazione

	ADC3->ISR |= ADC_ISR_ADRDY;		// Azzero il bit prima del controllo
	ADC3->CR |= ADC_CR_ADEN;		// Accendo l' ADC

	while((ADC3->ISR & ADC_ISR_ADRDY) != 0){}

	ADC3->ISR |= ADC_ISR_ADRDY;		// Azzero il Ready bit
	// Fine accensione

	/* ADR ACCESO */

	// TIM6 set to 240Mhz

	TIM6->PSC = 12; // TIM6 CLOCK/PSC
	TIM6->ARR = 20;	// TIM6 CLOCK/PSC/ARR
	TIM6->CNT = 0;
	TIM6->DIER &= ~TIM_DIER_UIE;

	// 240 Mhz -> 20 Mhz -> 1 Mhz

	ADC3->IER |= ADC_IER_EOCIE;
}



void ADC_custom_interrupt_pre(){

	if(triggd && (DMA2_Stream0->NDTR == trig_indx)){

		TIM6->CR1 &= ~TIM_CR1_CEN;
		ADC3->ISR |= ADC_ISR_EOC;

		triggd = false;

		USART3->CR3 |= USART_CR3_DMAT;
		return;

	}else if(!pre_triggd && !triggd && !(bool)(COMP12->SR & COMP_SR_C2VAL)){

		pre_triggd = true;
		return;

	}else if(pre_triggd && !triggd && (bool)(COMP12->SR & COMP_SR_C2VAL)){

		trig_indx = (DMA2_Stream0->NDTR);
		triggd = true;
		pre_triggd = false;
		return;
	}
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










