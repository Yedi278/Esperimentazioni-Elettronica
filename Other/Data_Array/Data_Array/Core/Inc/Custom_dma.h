/*
 * Custom_dma.h
 *
 *  Created on: Oct 30, 2024
 *      Author: yehan
 */
#ifndef CUSTOM_DMA_H
#define CUSTOM_DMA_H

#include <stdint.h>
#include <stdbool.h>
#include <stm32h743xx.h>

#define DMA_SINGLE_DATA_BUFF_SIZE 100UL
#define DMA_N_DATA_SETS 10UL

extern uint16_t DMA_data_buffer[DMA_N_DATA_SETS][DMA_SINGLE_DATA_BUFF_SIZE];

void DMA_custom_init();

void DMA_custom_interrupt_tx();

void DMA_custom_interrupt_rx();

#endif //CUSTOM_DAM_H
