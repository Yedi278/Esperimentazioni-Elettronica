/*
 * Custom_ADC.h
 *
 *  Created on: Dec 2, 2024
 *      Author: yehan
 */

#ifndef CUSTOM_ADC_H_
#define CUSTOM_ADC_H_

#include <stdint.h>
#include "stm32h743xx.h"

#define TS_CAL_30C 	*(uint16_t*)(0x1FF1E820)
#define TS_CAL_110C *(uint16_t*)(0x1FF1E840)

#define BUFFER_SIZE 100UL
extern uint16_t data_buffer[];



void adc_custom_init();

void adc_custom_interr();


#endif /* CUSTOM_ADC_H_ */
