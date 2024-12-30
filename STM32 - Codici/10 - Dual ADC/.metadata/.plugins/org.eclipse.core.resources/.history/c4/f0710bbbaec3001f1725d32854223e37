/*
 * Custom_COMP.c
 *
 *  Created on: Dec 7, 2024
 *      Author: yehan
 */

#include "Custom_COMP.h"

bool triggd = 	 false;
bool acquiring = false;
bool enable = 	 false;
bool pre_triggd = false;

void blink(){
	if(GPIOE->IDR & GPIO_IDR_ID1){
		GPIOE->BSRR |= GPIO_BSRR_BR1;
	}else{
		GPIOE->BSRR |= GPIO_BSRR_BS1;
	}
}

void COMP_custom_init(){

	DAC1->CR |= DAC_CR_EN1;			// attivo DAC

	DAC1->DHR12R1 = V_to_uint12_t(0.8);			// imposto soglia del comparatore IN 12 BIT NON 16

	DAC1->SWTRIGR |= DAC_SWTRIGR_SWTRIG1;

	COMP2->CFGR |= COMP_CFGRx_EN;	// attivo il comparatore

	triggd = false;
	acquiring = false;
	enable = false;
	pre_triggd = false;
}

void TIM7_custom_interrupt(){
	if(!acquiring){
		if(COMP12->SR & COMP_SR_C2VAL){
			if(pre_triggd){
				acquiring = true;
				TIM6->CR1 |= TIM_CR1_CEN;
				TIM7->CR1 &= ~TIM_CR1_CEN;
				pre_triggd = false;
				return;
			}
		}else{
			pre_triggd = true;
			return;
		}
	}
}



