/*
 * custom_adc.c
 *
 *  Created on: Oct 24, 2024
 *      Author: yehan
 */

#include "custom_adc.h"

uint16_t data_buffer[1000]={0};
int data_buffer_write_index = 0;
bool reading = false;
bool triggered = false;
uint16_t old_raw_data=0;
uint16_t raw_data;

void adc3_init(){

	ADC3->SQR1=0; // Resetto il registro per cancellare modifice dell'IDE

	ADC3->SQR1 |= (0 << ADC_SQR1_L_Pos);	// Indico quanti canali leggere (0 = 1 canale)

	ADC3->SQR1 |= (0 << ADC_SQR1_SQ1_Pos);	// Inidco i canali da accendere

	ADC3->PCSEL |= ADC_PCSEL_PCSEL_0;		// Selezioni i canali da leggere

	// Tipicamente gestiti dall'IDE
	//	ADC3->CR &= ~ADC_CR_DEEPPWD;
	//	ADC3->CR |= ADC_CR_ADVREGEN;
	//	while((ADC3->ISR & ADC_ISR_LDORDY) != 1){}

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
	TIM6->PSC = 48;
	TIM6->ARR = 10;
	TIM6->CNT = 0;
	TIM6->DIER |= TIM_DIER_UIE;
	TIM6->CR1 |= TIM_CR1_CEN;
	/* Fine sett. TImer */

	ADC3->IER |= ADC_IER_EOCIE;		// Abilito l'interrupt di fine conversione
	ADC3->CR  |= ADC_CR_ADSTART;	// Inizio le misurazioni
}




void adc3_interrupt(){

	extern int data_buffer_write_index;
	extern uint16_t data_buffer[1000];


	if((ADC3->ISR & ADC_ISR_EOC) && !reading){

		if(data_buffer_write_index < 1000){

			raw_data = ADC3->DR;

			if(triggered){
				data_buffer[data_buffer_write_index] = raw_data;
				old_raw_data = raw_data;
				++data_buffer_write_index;
			}
			else{
				if(raw_data > (uint16_t)PRETRIG_VALUE && raw_data < (uint16_t)TRIG_VALUE
						&& old_raw_data < raw_data){

					triggered = true;
					data_buffer[data_buffer_write_index] = raw_data;
					old_raw_data = raw_data;
					++data_buffer_write_index;

				}else{

					old_raw_data = raw_data;
				}
			}

		}else{
			data_buffer[0] = raw_data;
			old_raw_data = raw_data;
			data_buffer_write_index=0;
			triggered = false;
		}

	}else{
		ADC3->ISR |= ADC_ISR_EOC;
	}
}








