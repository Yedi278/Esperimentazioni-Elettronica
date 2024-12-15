/*
 * HALL.h
 *
 *  Created on: Nov 15, 2024
 *      Author: yehan
 */

#ifndef INC_HALL_H_
#define INC_HALL_H_

#include "stm32h743xx.h"
#include <stdint.h>

void USART3_custom_init();

void USART3_custom_interrupt();

void Hall_0_interr();
void Hall_1_interr();
void Hall_2_interr();

#endif /* INC_HALL_H_ */
