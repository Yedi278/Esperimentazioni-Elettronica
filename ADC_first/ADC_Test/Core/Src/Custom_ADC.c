/*
 * Custom_ADC.c
 *
 *  Created on: Oct 17, 2024
 *      Author: yehan
 */
#include "Custom_ADC.h"


uint32_t Const_1 = (uint32_t)80000UL;
uint32_t Const_2 = (uint32_t)30000UL;

int ADC3_interr_number = 0;

void ADC_custom_init(){


//	ADC3->CR &= ~ADC_CR_ADSTART;
	ADC3->SQR1=0; // per azzerare la configurazione dell'ide

	ADC3->SQR1 |= (19 << ADC_SQR1_SQ1_Pos) | (18 << ADC_SQR1_SQ2_Pos);


	ADC3->SQR1 |= (1 << ADC_SQR1_L_Pos);	// Indico quanti canali leggere : 2

	ADC3->PCSEL |= ADC_PCSEL_PCSEL_19 | ADC_PCSEL_PCSEL_18; // Dichiaro quali canali leggere : 18 e 19

	// Tipicamente gestiti dall'IDE
//	ADC3->CR &= ~ADC_CR_DEEPPWD;

//	ADC3->CR |= ADC_CR_ADVREGEN;
//
//	while((ADC3->ISR & ADC_ISR_LDORDY) != 1){}

	/* Calibrazione */

	ADC3->CR &= ~ADC_CR_ADCALDIF;   // Imposto misura single read;
	ADC3->CR |= ADC_CR_ADCALLIN;	// Calibrazione Lineare con offset

	ADC3->CR &= ~ADC_CR_ADEN;		// Occorre ADC spento

	ADC3->CR |= ADC_CR_ADCAL;		// Inizio calibrazione

	uint16_t i=0;
	while((ADC3->CR & ADC_CR_ADCAL) != 0){
		++i;
	}
	++i;
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

	ADC3->SMPR2 |= (7 << ADC_SMPR2_SMP18_Pos);	// Indico Il tempo prima della misura
	ADC3_COMMON->CCR |= ADC_CCR_TSEN;			// Abilito il termometro
	ADC3->CR |= ADC_CR_ADSTART;

	ADC3->SMPR2 |= (30 << ADC_SMPR2_SMP19_Pos);
	ADC3_COMMON->CCR |= ADC_CCR_VREFEN;

	ADC3->IER |= ADC_IER_EOCIE;					// Abilito l'interrupt di fine conversione
}

void ADC_custom_interrupt(){
	extern int ADC3_interr_number;


	if(ADC3_interr_number == 0){

		uint16_t voltage_raw = ADC3->DR;
		uint32_t V_calibrata = ( (uint32_t)3300000 / (uint32_t)voltage_raw ) * (uint32_t)VREFINT_C;
		++ADC3_interr_number;

	}else if(ADC3_interr_number == 1){

		uint16_t temp_raw = ADC3->DR;
		uint32_t temp = ((Const_1*((uint32_t)(temp_raw - TS_CAL_30C))) / (uint32_t)(TS_CAL_110C - TS_CAL_30C) ) + Const_2;
		ADC3_interr_number = 0;
	}
}














