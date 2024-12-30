/*
 * Custom_DMA.c
 *
 *  Created on: Dec 6, 2024
 *      Author: yehan
 */

#include "Custom_DMA.h"
#include "Custom_ADC.h"

#define DMA_DATA_BUFF_SIZE 1000

uint16_t DMA_data_buffer[DMA_DATA_BUFF_SIZE];

void DMA_custom_init(){

	DMA1_Stream0->M0AR = (uint32_t) (&DMA_data_buffer);	// inidico l'indirizzo dello storarge di dati
	DMA1_Stream1->M0AR = (uint32_t) (&DMA_data_buffer);

	DMA1_Stream0->PAR = (uint32_t) (&ADC3->DR);			// indico gli indirizzi per la trasmissione
	DMA1_Stream1->PAR = (uint32_t) (&USART3->TDR);

	DMA1_Stream0->NDTR = DMA_DATA_BUFF_SIZE;			// numero elementi da prendere da ADC3
	DMA1_Stream1->NDTR = DMA_DATA_BUFF_SIZE*2;			// numero elementi da mandare a USART3

	DMA1_Stream0->CR |= DMA_SxCR_TCIE;		// disablilito interrupt di fine ricezione
	DMA1_Stream1->CR |= DMA_SxCR_TCIE;		// abilito interrupt di fine trasmissione

	ADC3->CFGR |= (3 << ADC_CFGR_DMNGT_Pos);	// DMA in cont mode

	DMA1_Stream0->CR |= DMA_SxCR_EN;
	DMA1_Stream1->CR |= DMA_SxCR_EN;

	ADC3->CR  |= ADC_CR_ADSTART;
}

void DMA_custom_interrupt_tx(){


	USART3->CR3 &= ~USART_CR3_DMAT;			  // SPENGO trasmissione usart

	DMA1->LIFCR = 0xffffffff;	// azzero i flag di interrupt per evitare che ci entri mentre avviene l'interrupt
	DMA1->HIFCR = 0xffffffff;


	extern bool acquiring;
	extern bool pre_triggd;

	acquiring = false;
	DMA1_Stream0->NDTR = DMA_DATA_BUFF_SIZE;			// numero elementi da prendere da ADC3
	pre_triggd = false;

	DMA1_Stream0->CR |= DMA_SxCR_EN;
	DMA1_Stream1->CR |= DMA_SxCR_EN;
//	TIM7->CR1 |= TIM_CR1_CEN;

}

void DMA_custom_interrupt_rx(){

	TIM6->CR1 &= ~TIM_CR1_CEN;

	DMA1->LIFCR = 0xffffffff;	// azzero i flag di interrupt per evitare che ci entri mentre avviene l'interrupt
	DMA1->HIFCR = 0xffffffff;

	DMA1_Stream1->NDTR = DMA_DATA_BUFF_SIZE*2;

	USART3->CR3 |= USART_CR3_DMAT;
}








