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

/* FUNCTIONS */

void usart3_init();

void usart3_custom_interrupt();

#endif /* CUSTOM_USART_H_ */