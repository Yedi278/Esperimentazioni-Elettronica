/*
 * Custom_ADC.h
 *
 *  Created on: Oct 17, 2024
 *      Author: yehan
 */

#ifndef INC_CUSTOM_ADC_H_
#define INC_CUSTOM_ADC_H_

#include "stm32h743xx.h"
#include <stdint.h>
#include <stdbool.h>

#define VREFINT_C 	*(uint16_t*)(0x1FF1E860)
#define PRETRIG_VALUE	400UL
#define TRIG_VALUE		2000UL

extern volatile bool pre_triggd;
extern volatile bool triggd;
extern volatile uint16_t trig_indx;
extern volatile uint16_t n_data_index;

void ADCx_custom_init(ADC_TypeDef *ADCx, uint8_t INx_Pin);

void ADC_custom_init();

void ADC_custom_interrupt();

void COMP_custom_interrupt();

#endif /* INC_CUSTOM_ADC_H_ */