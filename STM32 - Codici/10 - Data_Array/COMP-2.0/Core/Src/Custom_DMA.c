/*
 * Custom_DMA.c
 *
 *  Created on: Dec 6, 2024
 *      Author: yehan
 */

#include "Custom_DMA.h"
#include "Custom_ADC.h"

uint16_t DMA_data_buffer[DATA_COUNTS][DATA_LENGTH];
uint16_t data_index=0;

void DMA_custom_init(){

	data_index = 0;

	DMA1_Stream0->M0AR = (uint32_t) (&DMA_data_buffer[0][0]);	// inidico l'indirizzo dello storarge di dati
	DMA1_Stream1->M0AR = (uint32_t) (&DMA_data_buffer[0][0]);

	DMA1_Stream0->PAR = (uint32_t) (&ADC3->DR);			// indico gli indirizzi per la trasmissione
	DMA1_Stream1->PAR = (uint32_t) (&USART3->TDR);

	DMA1_Stream0->NDTR = DATA_LENGTH;			// numero elementi da prendere da ADC3
	DMA1_Stream1->NDTR = DATA_LENGTH*2*DATA_COUNTS;			// numero elementi da mandare a USART3

	DMA1_Stream0->CR |= DMA_SxCR_TCIE;		// ablilito interrupt di fine ricezione
	DMA1_Stream1->CR |= DMA_SxCR_TCIE;		// abilito interrupt di fine trasmissione

	ADC3->CFGR |= (3 << ADC_CFGR_DMNGT_Pos);	// DMA in cont mode

	DMA1_Stream0->CR |= DMA_SxCR_EN;
	DMA1_Stream1->CR |= DMA_SxCR_EN;

	ADC3->CR |= ADC_CR_ADSTART;
}

void DMA_custom_interrupt_tx(){

	USART3->CR3 &= ~USART_CR3_DMAT;			  // SPENGO trasmissione usart

	DMA1->LIFCR = 0xffffffff;	// azzero i flag di interrupt per evitare che ci entri mentre avviene l'interrupt
	DMA1->HIFCR = 0xffffffff;

	acquiring = false;
	DMA1_Stream0->NDTR = DATA_LENGTH;			// numero elementi da prendere da ADC3
	pre_triggd = false;

	DMA1_Stream0->CR |= DMA_SxCR_EN;
	DMA1_Stream1->CR |= DMA_SxCR_EN;
}

void DMA_custom_interrupt_rx(){

	TIM6->CR1 &= ~TIM_CR1_CEN;

	DMA1->LIFCR = 0xffffffff;	// azzero i flag di interrupt per evitare che ci entri mentre avviene l'interrupt
	DMA1->HIFCR = 0xffffffff;


	if(data_index < DATA_COUNTS){
		DMA1_Stream0->M0AR = (uint32_t)(&DMA_data_buffer[data_index][0]);
		DMA1_Stream0->NDTR = DATA_LENGTH;
		data_index++;
		acquiring = false;

		DMA1_Stream0->CR |= DMA_SxCR_EN;
		TIM7->CR1 |= TIM_CR1_CEN;
		return;

	}else{
		data_index = 0;
		DMA1_Stream1->CR |= DMA_SxCR_EN;
		USART3->CR3 |= USART_CR3_DMAT;
	}
}








