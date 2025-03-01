/*
 * Custom_ADC.c
 *
 *  Created on: Dec 2, 2024
 *      Author: yehan
 */

#include "Custom_ADC.h"

uint16_t data_buffer[BUFFER_SIZE];
uint8_t *data_buffer_char_p = data_buffer;
uint16_t data_buffer_index;

void adc_custom_init(){

	ADC3->CR &= ~ADC_CR_ADSTART;

	ADC3->SQR1 = 0; // per azzerare la configurazione dell'ide

	ADC3->SQR1 |= (0 << ADC_SQR1_L_Pos);	// Indico quanti canali leggere 0=1

	ADC3->SQR1 |= (18 << ADC_SQR1_SQ1_Pos);

	ADC3->PCSEL = 0;
	ADC3->PCSEL |= (1 << (ADC_PCSEL_PCSEL_Pos + 18)); // Dichiaro quali canali leggere : 18 e 19

	/* Calibrazione */
	ADC3->CR &= ~ADC_CR_ADCALDIF;   // Imposto misura single read;
	ADC3->CR |= ADC_CR_ADCALLIN;	// Calibrazione Lineare con offset
	ADC3->CR &= ~ADC_CR_ADEN;		// Occorre ADC spento
	ADC3->CR |= ADC_CR_ADCAL;		// Inizio calibrazione


	while((ADC3->CR & ADC_CR_ADCAL) != 0){}
	// FIne calibrazione

	ADC3->ISR |= ADC_ISR_ADRDY;		// Azzero il bit prima del controllo
	ADC3->CR |= ADC_CR_ADEN;		// Accendo l' ADC

	while((ADC3->ISR & ADC_ISR_ADRDY) != 0){}

	ADC3->ISR |= ADC_ISR_ADRDY;		// Azzero il Ready bit
	// Fine accensione

	/* ADR INIZIALIZZATO */

	ADC3->SMPR2 |= (7 << ADC_SMPR2_SMP18_Pos);	// Indico Il tempo prima della misura

	TIM6->PSC = 48;
	TIM6->ARR = 1000;
	TIM6->CNT = 0;
	TIM6->DIER &= ~TIM_DIER_UIE;
	TIM6->CR1 |= TIM_CR1_CEN;

	ADC3->IER |= ADC_IER_EOCIE;					// Abilito l'interrupt di fine conversione
	ADC3->CR  |= ADC_CR_ADSTART;				// Inizio le misurazioni
}


void adc_custom_interr(){

	if(data_buffer_index < BUFFER_SIZE){

		data_buffer[data_buffer_index] = ADC3->DR;
	}
	else{
		data_buffer_index=0;
		data_buffer[0] = ADC3->DR;
	}

	++data_buffer_index;
}




















