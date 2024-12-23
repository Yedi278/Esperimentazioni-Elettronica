/*
 * Custom_usart.c
 *
 *  Created on: Oct 17, 2024
 *      Author: yehan
 */

#include "Custom_usart.h"
#include "Custom_dma.h"
#include <stdint.h>

void usart3_init(){

    USART3->CR1 |= USART_CR1_TE;
    USART3->CR1 |= USART_CR1_RE;

    USART3->CR1 &= ~USART_CR1_TXEIE;
    USART3->CR1 |= USART_CR1_RXNEIE;

    USART3->CR1 |= USART_CR1_UE;

}

void usart3_custom_interrupt(){

	char data = USART3->RDR;
	extern volatile bool triggd;
	extern volatile uint16_t n_data_index;

	if(data == 'V'){

		USART3->TDR = ((unsigned char*)&VREFINT_C) [0];
		while(!(USART3->ISR & USART_ISR_TXE_TXFNF));
		USART3->TDR = ((unsigned char*)&VREFINT_C) [1];
		while(!(USART3->ISR & USART_ISR_TXE_TXFNF));

	}else if(data == '?'){
//		USART3->CR3 &= ~USART_CR3_DMAT;	// spengo l'usart
		DMA2_Stream1->CR &= ~DMA_SxCR_EN;

		DMA2_Stream0->CR &= ~DMA_SxCR_EN;
		DMA2_Stream0->M0AR = (uint32_t)(&DMA_data_buffer[0][0]);
		DMA2_Stream0->NDTR = DMA_SINGLE_DATA_BUFF_SIZE;

		DMA2_Stream0->CR |= DMA_SxCR_EN;
		n_data_index = 0;

		triggd = false;

		TIM6->CR1 |= TIM_CR1_CEN;		// accendo l'adc

	}

	USART3->ICR |= USART_ICR_ORECF; //Cancella l'overrun. Capita quando si entra in debug
	USART3->ICR |= USART_ICR_TCCF;  //Azzeramento flag interrupt trasmissione
	USART3->RQR |= USART_RQR_RXFRQ;  //Azzeramento flag interrupt ricezione
}
