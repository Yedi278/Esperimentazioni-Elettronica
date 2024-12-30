/*
 * Custom_USART.h
 *
 *  Created on: Dec 6, 2024
 *      Author: yehan
 */

#ifndef INC_CUSTOM_USART_H_
#define INC_CUSTOM_USART_H_

#include "stm32h743xx.h"
#include <stdint.h>
#include <stdbool.h>


void USART_custom_init();

void USART_custom_interrupt();


#endif /* INC_CUSTOM_USART_H_ */
