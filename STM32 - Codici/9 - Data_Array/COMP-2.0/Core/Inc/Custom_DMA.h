/*
 * Custom_DMA.h
 *
 *  Created on: Dec 6, 2024
 *      Author: yehan
 */

#ifndef INC_CUSTOM_DMA_H_
#define INC_CUSTOM_DMA_H_

#include <stdint.h>
#include <stdbool.h>
#include <stm32h743xx.h>

#define DATA_LENGTH 400UL
#define DATA_COUNTS 4UL

extern uint16_t DMA_data_buffer[][DATA_LENGTH];
extern uint16_t data_index;
extern bool acquiring;
extern bool pre_triggd;

void DMA_custom_init();

void DMA_custom_interrupt_tx();

void DMA_custom_interrupt_rx();

#endif /* INC_CUSTOM_DMA_H_ */
