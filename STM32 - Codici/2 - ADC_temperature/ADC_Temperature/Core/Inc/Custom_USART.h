/*
 * Custom_USART.h
 *
 *  Created on: Dec 2, 2024
 *      Author: yehan
 */

#ifndef INC_CUSTOM_USART_H_
#define INC_CUSTOM_USART_H_

#include "stm32h743xx.h"
#include <stdint.h>
#include "Custom_ADC.h"

extern uint16_t data_buffer[BUFFER_SIZE];
extern uint8_t *data_buffer_char_p;
extern uint16_t data_buffer_index;

extern uint16_t tx_buff_index;

void usart_custom_init();

void usart_custom_interr();



#endif /* INC_CUSTOM_USART_H_ */
