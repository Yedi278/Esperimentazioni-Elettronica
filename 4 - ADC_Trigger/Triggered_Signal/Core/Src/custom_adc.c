/*
 * custom_adc.c
 *
 *  Created on: Oct 24, 2024
 *      Author: yehan
 */

#include "custom_adc.h"

uint16_t data[1000]={0};
uint16_t data_index = 0;
uint16_t raw_data;

bool triggd=false;
bool pretriggd=false;


void adc3_init(){

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
	TIM6->ARR = 15;	// 20Mhz / 10 = 2Mhz
	TIM6->CNT = 0;
	TIM6->DIER &= ~TIM_DIER_UIE;
	TIM6->CR1 |= TIM_CR1_CEN;
	/* Fine sett. TImer */

	ADC3->IER |= ADC_IER_EOCIE;		// Abilito l'interrupt di fine conversione
	ADC3->CR  |= ADC_CR_ADSTART;	// Inizio le misurazioni
}


void adc3_interrupt(){

	raw_data = ADC3->DR;	// leggo il dato dall'ADC

	if(triggd){				// controllo se nello stato triggerato

		if(data_index < 1000UL){	// verifico di non essere oltre grandezza buffer

			data[data_index] = ADC3->DR;
			++data_index;
			return;
		}
		else{						// finisco la presa dati

			TIM6->CR1 &= ~TIM_CR1_CEN;
			triggd = false;
			data_index = 0;
			USART3->CR1 |= USART_CR1_TCIE;
			return;
		}
	}
	else{

		if(!pretriggd){				// verifico condizioni pretrigger
			if(raw_data < PRETRIG_VALUE){
				pretriggd = true;
				return;
			}
			return;
		}

		if(raw_data > TRIG_VALUE){	// verifico condizioni di trigger
			triggd = true;
			pretriggd = false;
			return;
		}
		return;
	}
}








