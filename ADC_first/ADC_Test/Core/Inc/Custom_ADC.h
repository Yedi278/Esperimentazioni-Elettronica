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


/* Valori di Riferimento a livello macchina */
#define TS_CAL_30C 	*(uint16_t*)(0x1FF1E820)
#define TS_CAL_110C *(uint16_t*)(0x1FF1E840)
#define VREFINT_C 	*(uint16_t*)(0x1FF1E860)

/**
 *
 */
void ADC_custom_init();

/**
 *
 */
void ADC_start();

void ADC_convert_buffer();

void ADC_custom_interrupt();

#endif /* INC_CUSTOM_ADC_H_ */
