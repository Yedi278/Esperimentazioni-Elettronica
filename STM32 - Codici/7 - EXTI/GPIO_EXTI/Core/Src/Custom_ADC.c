/*
 * Custom_ADC.c
 *
 *  Created on: Dec 6, 2024
 *      Author: yehan
 */

#include "Custom_ADC.h"

bool triggd = false;
bool pre_triggd = false;
uint16_t trig_indx = 0;


void ADC_custom_init(){

	ADC3->SQR1=0; // Resetto il registro per cancellare modifice dell'IDE

	ADC3->SQR1 |= (0 << ADC_SQR1_L_Pos);	// Indico quanti canali leggere (0 = 1 canale)

	ADC3->SQR1 |= (0 << ADC_SQR1_SQ1_Pos);	// Inidco i canali da accendere

	ADC3->PCSEL |= ADC_PCSEL_PCSEL_0;		// Selezioni i canali da leggere

	/* Fase di calibrazione */
	ADC3->CR &= ~ADC_CR_ADCALDIF;   // Imposto misura single read;
	ADC3->CR |= ADC_CR_ADCALLIN;	// Calibrazione Lineare con offset
	ADC3->CR &= ~ADC_CR_ADEN;		// Occorre ADC spento
	ADC3->CR |= ADC_CR_ADCAL;		// Inizio calibrazione

	while((ADC3->CR & ADC_CR_ADCAL) != 0){};
	/* Fine fase di calibrazione */

	/* Accensione ADC */
	ADC3->ISR |= ADC_ISR_ADRDY;		// Azzero il bit prima del controllo
	ADC3->CR |= ADC_CR_ADEN;		// Abilito l'ADC

	while((ADC3->ISR & ADC_ISR_ADRDY) != 0){}	// Aspetto che il flag cambi

	ADC3->ISR |= ADC_ISR_ADRDY;		// Azzero il Ready bit
	/* Fine istruzioni per l'accensione */

	/* Impostazioni TIMER per triggerare l'nizio della misura */
	TIM6->PSC = 12;	// 240/12 = 20Mhz
	TIM6->ARR = 1;	// 20Mhz / 10 = 2Mhz
	TIM6->CNT = 0;
	TIM6->DIER &= ~TIM_DIER_UIE;
	TIM6->CR1 &= ~TIM_CR1_CEN;
	/* Fine sett. TImer */

	ADC3->IER |= ADC_IER_EOCIE;		// Abilito l'interrupt di fine conversione
//	ADC3->CR  |= ADC_CR_ADSTART;	// Inizio le misurazioni
}


void EXTI_custom_interrupt(){

	if((TIM6->CR1 & TIM_CR1_CEN) == 0 && (USART->CR3 & USART_CR3_DMAT) == 0){	// se il timer è spento

		DMA1_Stream0->NDTR = 1000;		// imposto numero di misure da eseguire

		GPIOB->BSRR |= GPIO_BSRR_BS0;

		TIM6->CR1 |= TIM_CR1_CEN;		// accendo il timer
	}
}





