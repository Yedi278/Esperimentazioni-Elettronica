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

#define PRETRIG_VALUE	2500UL
#define TRIG_VALUE		3000UL

void ADC_custom_init();

#endif /* INC_CUSTOM_ADC_H_ */