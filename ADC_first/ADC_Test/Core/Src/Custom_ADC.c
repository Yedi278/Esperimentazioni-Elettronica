/*
 * Custom_ADC.c
 *
 *  Created on: Oct 17, 2024
 *      Author: yehan
 */
#include "Custom_ADC.h"


uint32_t temp_buffer[1000];
int temp_buff_index=0;


void ADC_custom_init(){


//	ADC3->CR &= ~ADC_CR_ADSTART;
	ADC3->SQR1=0; // per azzerare la configurazione dell'ide

	ADC3->SQR1 |= (18 << ADC_SQR1_SQ1_Pos);
//	ADC3->SQR1 |= (18 << ADC_SQR1_SQ2_Pos);

	ADC3->SQR1 &= ~(1 << ADC_SQR1_L_Pos);	// Indico quanti canali leggere

	ADC3->PCSEL |= ADC_PCSEL_PCSEL_18; // Dichiaro quali canali leggere : 18 e 19
//	ADC3->PCSEL |= ADC_PCSEL_PCSEL_19;

	// Tipicamente gestiti dall'IDE
//	ADC3->CR &= ~ADC_CR_DEEPPWD;
//	ADC3->CR |= ADC_CR_ADVREGEN;
//	while((ADC3->ISR & ADC_ISR_LDORDY) != 1){}

	/* Calibrazione */
	ADC3->CR &= ~ADC_CR_ADCALDIF;   // Imposto misura single read;
	ADC3->CR |= ADC_CR_ADCALLIN;	// Calibrazione Lineare con offset
	ADC3->CR &= ~ADC_CR_ADEN;		// Occorre ADC spento
	ADC3->CR |= ADC_CR_ADCAL;		// Inizio calibrazione


	while((ADC3->CR & ADC_CR_ADCAL) != 0){};
	// FIne calibrazione
}

void ADC_start(){
	/* Accensione ADC */

	ADC3->ISR |= ADC_ISR_ADRDY;		// Azzero il bit prima del controllo
	ADC3->CR |= ADC_CR_ADEN;		// Accendo l' ADC

	while((ADC3->ISR & ADC_ISR_ADRDY) != 0){}

	ADC3->ISR |= ADC_ISR_ADRDY;		// Azzero il Ready bit
	// Fine accensione

	/* ADR ACCESO */
//	ADC3_COMMON->CCR |= 0xb << ADC_CCR_PRESC_Pos; // Imposto un prescaler per il clock in modo da aver misure più precise di temperatura

	ADC3->CFGR |= ADC_CFGR_CONT;				// Imposto la modalità di misura continua
	ADC3->CFGR |= ADC_CFGR_AUTDLY;				// Evito l'overrun: misuro solo dopo aver finito la precedente misura

	ADC3->SMPR2 |= (7 << ADC_SMPR2_SMP18_Pos);	// Indico Il tempo prima della misura
//	ADC3->SMPR2 |= (7 << ADC_SMPR2_SMP19_Pos);

	ADC3_COMMON->CCR |= ADC_CCR_TSEN;			// Abilito il termometro
//	ADC3_COMMON->CCR |= ADC_CCR_VREFEN;			// Abilito la tensione di riferimento


	ADC3->IER |= ADC_IER_EOCIE;					// Abilito l'interrupt di fine conversione
	ADC3->CR  |= ADC_CR_ADSTART;				// Inizio le misurazioni
}

void ADC_custom_interrupt(){

	extern int ADC3_interr_number;
	extern uint32_t temp_buffer[];
	extern int temp_buff_index;


	uint16_t data_raw = ADC3->DR;

	uint32_t temp = ( ( 80000UL * (uint32_t)(data_raw - TS_CAL_30C) ) / (uint32_t)(TS_CAL_110C - TS_CAL_30C) ) + 30000UL;

	if(temp_buff_index < sizeof(temp_buffer)/sizeof(temp_buffer[0])){

			temp_buffer[temp_buff_index] = temp;
			++temp_buff_index;
	}
}














