/*
 * Custom_ADC.c
 *
 *  Created on: Dec 6, 2024
 *      Author: yehan
 */

#include "Custom_ADC.h"


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

	/*	IN0 -> PIN PC2 o A4 */
	ADCx_custom_init(ADC3, 0);
	ADC3->IER &= ~ADC_IER_EOCIE;	// interrupt ADC
	ADCx_custom_init(ADC1, 19);
	ADC1->IER &= ~ADC_IER_EOCIE;	// interrupt ADC


	// TIM6 set to 240Mhz
	TIM6->PSC = 1; // TIM6 CLOCK/PSC
	TIM6->ARR = 1;	// TIM6 CLOCK/PSC/ARR
	TIM6->CNT = 0;
	TIM6->DIER &= ~TIM_DIER_UIE;

	TIM7->PSC = 1;
	TIM7->ARR = 1;
	TIM7->CNT = 0;
	TIM7->DIER |= TIM_DIER_UIE;
	TIM7->CR1 &= ~TIM_CR1_CEN;
}







