/*
 * Custom_COMP.c
 *
 *  Created on: Dec 7, 2024
 *      Author: yehan
 */

#include "Custom_COMP.h"

void COMP_custom_init(){

	DAC1->CR |= DAC_CR_EN1;			// attivo DAC

	DAC1->DHR12R1 = 100;			// imposto soglia del comparatore IN 12 BIT NON 16

	DAC1->SWTRIGR |= DAC_SWTRIGR_SWTRIG1;

	COMP2->CFGR |= COMP_CFGRx_EN;	// attivo il comparatore
}
