/*
 * Custom_dma.c
 *
 *      Author: yehan
 */

#include "Custom_dma.h"


#define DMA_DATA_BUFF_SIZE 1000UL


uint16_t DMA_data_buffer[2*DMA_DATA_BUFF_SIZE];


void DMA_custom_init(){

	ADC3->CR &= ~ADC_CR_ADSTART;
	ADC2->CR &= ~ADC_CR_ADSTART;

	DMA2_Stream0->CR &= ~DMA_SxCR_EN;	// Disattivo DMA per midificare i settaggi
	DMA2_Stream1->CR &= ~DMA_SxCR_EN;
	DMA2_Stream2->CR &= ~DMA_SxCR_EN;

	DMA2_Stream0->M0AR = (uint32_t) (&DMA_data_buffer);	// inidico l'indirizzo dello storarge di dati
	DMA2_Stream1->M0AR = (uint32_t) (&DMA_data_buffer);
	DMA2_Stream2->M0AR = (uint32_t) (&DMA_data_buffer[DMA_DATA_BUFF_SIZE]);

	DMA2_Stream0->PAR = (uint32_t) (&ADC3->DR);			// indico gli indirizzi per la trasmissione
	DMA2_Stream1->PAR = (uint32_t) (&USART3->TDR);
	DMA2_Stream2->PAR = (uint32_t) (&ADC2->DR);

	uint32_t n_misure = DMA_DATA_BUFF_SIZE;

	DMA2_Stream0->NDTR = n_misure;				// numero elementi da prendere da ADC3
	DMA2_Stream1->NDTR = n_misure*4;			// numero elementi da mandare a USART3
	DMA2_Stream2->NDTR = n_misure;

	DMA2_Stream0->CR &= ~DMA_SxCR_TCIE;		// disablilito interrupt di fine ricezione
	DMA2_Stream1->CR |= DMA_SxCR_TCIE;		// abilito interrupt di fine trasmissione
	DMA2_Stream2->CR &= ~DMA_SxCR_TCIE;

	ADC3->CFGR |= (3 << ADC_CFGR_DMNGT_Pos);	// Modalità iterazione DMA single,circular,etc
	ADC2->CFGR |= (3 << ADC_CFGR_DMNGT_Pos);

	DMA2_Stream0->CR |= DMA_SxCR_EN;
	DMA2_Stream1->CR |= DMA_SxCR_EN;
	DMA2_Stream2->CR |= DMA_SxCR_EN;

	ADC3->CR |= ADC_CR_ADSTART;
	ADC2->CR |= ADC_CR_ADSTART;

	//TIM6->CR1 |= TIM_CR1_CEN;	LO ACCENDO NELL'USART3 INTERR
}


void DMA_custom_interrupt_tx(){

	USART3->CR3 &= ~USART_CR3_DMAT;			  // SPENGO trasmissione usart

	extern uint16_t trig_indx;

	DMA2->LIFCR = 0xffffffff;	// azzero i flag di interrupt per evitare che ci entri mentre avviene l'interrupt
	DMA2->HIFCR = 0xffffffff;

	while(!(USART3->ISR & USART_ISR_TXE_TXFNF));
	USART3->TDR = ((unsigned char*)&trig_indx)[0];
	while(!(USART3->ISR & USART_ISR_TXE_TXFNF));
	USART3->TDR = ((unsigned char*)&trig_indx)[1];

	trig_indx = 0;

	DMA2_Stream0->CR |= DMA_SxCR_EN;
	DMA2_Stream1->CR |= DMA_SxCR_EN;
	DMA2_Stream2->CR |= DMA_SxCR_EN;
}














