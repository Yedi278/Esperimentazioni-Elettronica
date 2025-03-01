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

extern uint16_t data_buffer[];
extern uint16_t data_buffer_index;

extern uint16_t data_buffer_size;

void ADC_custom_init();

void ADC_convert_buffer();

void ADC_custom_interrupt();

#endif /* INC_CUSTOM_ADC_H_ */
