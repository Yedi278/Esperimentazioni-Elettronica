/*
 * Custom_ADC.h
 *
 *  Created on: Dec 6, 2024
 *      Author: yehan
 */

#ifndef INC_CUSTOM_ADC_H_
#define INC_CUSTOM_ADC_H_

#include "stm32h7xx_hal.h"
#include <stdint.h>
#include <stdbool.h>

#define PRETRIG_VALUE	1100UL
#define TRIG_VALUE		100UL

extern bool triggd;
extern bool pre_triggd;
extern uint16_t trig_indx;

void ADC_custom_init();

void ADC_custom_interrupt();

void EXTI_custom_interrupt();

#endif /* INC_CUSTOM_ADC_H_ */
