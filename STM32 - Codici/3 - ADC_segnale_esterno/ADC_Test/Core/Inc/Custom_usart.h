/*
 * Custom_usart.h
 *
 *  Created on: Oct 17, 2024
 *      Author: yehan
 */

#ifndef CUSTOM_USART_H_
#define CUSTOM_USART_H_

/* INCLUDE */

#include "stm32h743xx.h"
#include "Custom_ADC.h"
#include <stdint.h>

#define SIZE_OF_BUFF(x) sizeof(x)/sizeof(x[0])

extern uint16_t data_buffer[];
extern uint16_t data_buffer_index;
extern uint16_t data_buffer_size;

/* FUNCTIONS */

void init_usart3();

void usart3_interrupt();

#endif /* CUSTOM_USART_H_ */
