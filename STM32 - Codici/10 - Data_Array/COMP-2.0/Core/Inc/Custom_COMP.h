/*
 * Custom_COMP.h
 *
 *  Created on: Dec 7, 2024
 *      Author: yehan
 */

#ifndef INC_CUSTOM_COMP_H_
#define INC_CUSTOM_COMP_H_

#include "stm32h743xx.h"
#include <stdint.h>
#include <stdbool.h>

extern bool triggd;
extern bool acquiring;
extern bool enable;
extern bool pre_triggd;

#define V_to_uint12_t(x)(uint32_t)( (float)(3.3 * (float)(2 << 12)) / (float)x)

//#define SOGLIA_DAC  V_to_uint12_t(0.2)// ~0.8V

void COMP_custom_init();

void TIM7_custom_interrupt();

#endif /* INC_CUSTOM_COMP_H_ */
