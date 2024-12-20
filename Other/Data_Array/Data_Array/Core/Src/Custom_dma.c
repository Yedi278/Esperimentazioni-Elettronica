/*
 * Custom_dma.c
 *
 *      Author: yehan
 */

#include "Custom_dma.h"

uint16_t DMA_data_buffer[DMA_N_DATA_SETS][DMA_SINGLE_DATA_BUFF_SIZE];

void DMA_custom_init(){

	ADC3->CR &= ~ADC_CR_ADSTART;
	ADC2->CR &= ~ADC_CR_ADSTART;

	DMA2_Stream0->CR &= ~DMA_SxCR_EN;	// Disattivo DMA per midificare i settaggi
	DMA2_Stream1->CR &= ~DMA_SxCR_EN;

	DMA2_Stream0->PAR = (uint32_t )(&ADC3->DR);			// indico gli indirizzi per la trasmissione
	DMA2_Stream1->PAR = (uint32_t )(&USART3->TDR);

	// Memory Directions

	DMA2_Stream0->M0AR = (uint32_t )(&DMA_data_buffer[0][0]);	// inidico l'indirizzo dello storarge di dati
	DMA2_Stream1->M0AR = (uint32_t )(&DMA_data_buffer[0][0]);


	DMA2_Stream0->NDTR = DMA_SINGLE_DATA_BUFF_SIZE;				// numero elementi da prendere da ADC3
	DMA2_Stream1->NDTR = 2*DMA_N_DATA_SETS*DMA_SINGLE_DATA_BUFF_SIZE;			// numero elementi da mandare a USART3

	DMA2_Stream0->CR &= ~DMA_SxCR_TCIE;		// disablilito interrupt di fine ricezione
	DMA2_Stream1->CR |= DMA_SxCR_TCIE;		// abilito interrupt di fine trasmissione


	ADC3->CFGR |= (3 << ADC_CFGR_DMNGT_Pos);	// Modalità iterazione DMA single,circular,etc

	DMA2_Stream0->CR |= DMA_SxCR_EN;
	DMA2_Stream1->CR &= ~DMA_SxCR_EN;

	ADC3->CR |= ADC_CR_ADSTART;
	USART3->CR3 |= USART_CR3_DMAT;

	//TIM6->CR1 |= TIM_CR1_CEN;	LO ACCENDO NELL'USART3 INTERR
}


void DMA_custom_interrupt_tx(){

	DMA2->LIFCR = 0xffffffff;	// azzero i flag di interrupt per evitare che ci entri mentre avviene l'interrupt
	DMA2->HIFCR = 0xffffffff;

	DMA2_Stream1->CR &= ~DMA_SxCR_EN;
}














