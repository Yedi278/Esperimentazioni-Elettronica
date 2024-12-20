/*
 * Custom_dma.h
 *
 *  Created on: Oct 30, 2024
 *      Author: yehan
 */

#include <stdint.h>
#include <stdbool.h>
#include <stm32h743xx.h>

void DMA_custom_init();

void DMA_custom_interrupt_tx();

void DMA_custom_interrupt_rx();
