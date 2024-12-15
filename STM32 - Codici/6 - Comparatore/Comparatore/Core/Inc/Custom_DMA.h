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

extern uint16_t DMA_data_buffer[];

void DMA_custom_init();

void DMA_custom_interrupt_tx();

#endif /* INC_CUSTOM_DMA_H_ */
