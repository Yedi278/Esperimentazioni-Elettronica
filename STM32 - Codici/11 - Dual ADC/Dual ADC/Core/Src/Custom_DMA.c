/*
 * Custom_DMA.c
 *
 *  Created on: Dec 6, 2024
 *      Author: yehan
 */

#include "Custom_DMA.h"
#include "Custom_ADC.h"

uint16_t DMA_data_buffer[2*DATA_LENGTH];

uint16_t data_index=0;

void DMA_custom_init(){

	data_index = 0;

	DMA1_Stream0->M0AR = (uint32_t) (&DMA_data_buffer[0]);	// inidico l'indirizzo dello storarge di dati
	DMA1_Stream1->M0AR = (uint32_t) (&DMA_data_buffer[0]);
	DMA2_Stream0->M0AR = (uint32_t) (&DMA_data_buffer[DATA_LENGTH]);	// inidico l'indirizzo dello storarge di dati

	DMA1_Stream0->PAR = (uint32_t) (&ADC3->DR);			// indico gli indirizzi per la trasmissione
	DMA1_Stream1->PAR = (uint32_t) (&USART3->TDR);
	DMA2_Stream0->PAR = (uint32_t) (&ADC1->DR);

	DMA2_Stream0->NDTR = DATA_LENGTH;
	DMA1_Stream0->NDTR = DATA_LENGTH;			// numero elementi da prendere da ADC3
	DMA1_Stream1->NDTR = 2* (2*DATA_LENGTH);			// numero elementi da mandare a USART3

	DMA1_Stream0->CR |= DMA_SxCR_TCIE;		// ablilito interrupt di fine ricezione
	DMA1_Stream1->CR |= DMA_SxCR_TCIE;		// abilito interrupt di fine trasmissione
	DMA2_Stream0->CR &= ~DMA_SxCR_TCIE;

	ADC3->CFGR |= (3 << ADC_CFGR_DMNGT_Pos);	// DMA in cont mode
	ADC1->CFGR |= (3 << ADC_CFGR_DMNGT_Pos);

	DMA1_Stream0->CR |= DMA_SxCR_EN;
	DMA1_Stream1->CR &= ~DMA_SxCR_EN;
	DMA2_Stream0->CR |= DMA_SxCR_EN;

	ADC1->CR |= ADC_CR_ADSTART;
	ADC3->CR |= ADC_CR_ADSTART;
}

void DMA_custom_interrupt_tx(){

	USART3->CR3 &= ~USART_CR3_DMAT;			  // SPENGO trasmissione usart

	DMA1->LIFCR = 0xffffffff;
	DMA1->HIFCR = 0xffffffff;

	DMA1_Stream0->NDTR = DATA_LENGTH;			// numero elementi da prendere da ADC3
	DMA2_Stream0->NDTR = DATA_LENGTH;

	DMA1_Stream0->CR |= DMA_SxCR_EN;

	DMA2->LIFCR = 0xffffffff;
	DMA2->HIFCR = 0xffffffff;

	DMA2_Stream0->CR |= DMA_SxCR_EN;

	pre_triggd = false;
	acquiring = false;
}

void DMA_custom_interrupt_rx(){

	TIM6->CR1 &= ~TIM_CR1_CEN;

	DMA1->LIFCR = 0xffffffff;	// azzero i flag di interrupt per evitare che ci entri mentre avviene l'interrupt
	DMA1->HIFCR = 0xffffffff;

	while(DMA2_Stream0->NDTR != 0);

	DMA1_Stream1->NDTR = 2*2*DATA_LENGTH;
	DMA1_Stream1->CR |= DMA_SxCR_EN;
	USART3->CR3 |= USART_CR3_DMAT;
}

void DMA2_custom_interrupt(){

	DMA2->LIFCR = 0xffffffff;	// azzero i flag di interrupt per evitare che ci entri mentre avviene l'interrupt
	DMA2->HIFCR = 0xffffffff;

}






