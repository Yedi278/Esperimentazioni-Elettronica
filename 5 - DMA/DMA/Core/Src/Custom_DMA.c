/*
 * Custom_DMA.c
 *
 *  Created on: Dec 6, 2024
 *      Author: yehan
 */

#include "Custom_DMA.h"

#define DMA_DATA_BUFF_SIZE 1000

uint16_t DMA_data_buffer[DMA_DATA_BUFF_SIZE];

void DMA_custom_init(){

	DMA1_Stream0->M0AR = (uint32_t) (&DMA_data_buffer);	// inidico l'indirizzo dello storarge di dati
	DMA1_Stream1->M0AR = (uint32_t) (&DMA_data_buffer);

	DMA1_Stream0->PAR = (uint32_t) (&ADC3->DR);			// indico gli indirizzi per la trasmissione
	DMA1_Stream1->PAR = (uint32_t) (&USART3->TDR);

	uint32_t n_misure = DMA_DATA_BUFF_SIZE;

	DMA1_Stream0->NDTR = n_misure;			// numero elementi da prendere da ADC3
	DMA1_Stream1->NDTR = n_misure*2;			// numero elementi da mandare a USART3

	DMA1_Stream0->CR &= ~DMA_SxCR_TCIE;		// disablilito interrupt di fine ricezione
	DMA1_Stream1->CR |= DMA_SxCR_TCIE;		// abilito interrupt di fine trasmissione

	ADC3->CFGR |= (3 << ADC_CFGR_DMNGT_Pos);	// DMA in cont mode

	DMA1_Stream0->CR |= DMA_SxCR_EN;
	DMA1_Stream1->CR |= DMA_SxCR_EN;

	ADC3->CR  |= ADC_CR_ADSTART;

	//TIM6->CR1 |= TIM_CR1_CEN;	LO ACCENDO NELL'USART3 INTERR
}


void DMA_custom_interrupt_tx(){

	extern uint16_t trig_indx;

	USART3->CR3 &= ~USART_CR3_DMAT;			  // SPENGO trasmissione usart

	DMA1->LIFCR = 0xffffffff;	// azzero i flag di interrupt per evitare che ci entri mentre avviene l'interrupt
	DMA1->HIFCR = 0xffffffff;

	//ADC3->CFGR |= (1 << ADC_CFGR_DMNGT_Pos); // ACCENDO la ricezione di dati dall'adc

	DMA1_Stream0->CR |= DMA_SxCR_EN;
	DMA1_Stream1->CR |= DMA_SxCR_EN;

	while(!(USART3->ISR & USART_ISR_TXE_TXFNF));
	USART3->TDR = (unsigned char)(trig_indx & 0xFF );
	while(!(USART3->ISR & USART_ISR_TXE_TXFNF));
	USART3->TDR = *((unsigned char*)&trig_indx + 1);
	while(!(USART3->ISR & USART_ISR_TXE_TXFNF));

//	ADC3->CR |= ADC_CR_ADSTART;
	//TIM6->CR1 |= TIM_CR1_CEN;

//	USART3->CR3 |= USART_CR3_DMAT;
}


/**
 * @brief interrupt di ricezione di n dati dall'adc
 */
void DMA_custom_interrupt_rx(){

//	ADC3->CR &= ~ADC_CR_ADSTART;
//
//	ADC3->CFGR &= ~(1 << ADC_CFGR_DMNGT_Pos); // SPENGO la ricezione di dati dall'adc
//
//
//	DMA2->LIFCR = 0xffffffff;	// azzero i flag di interrupt per evitare che ci entri mentre avviene l'interrupt
//	DMA2->HIFCR = 0xffffffff;
//
//	USART3->CR3 |= USART_CR3_DMAT;			  // ATTVIO trasmissione usart
//
//	DMA2_Stream0->CR |= DMA_SxCR_EN;
//	DMA2_Stream1->CR |= DMA_SxCR_EN;
}