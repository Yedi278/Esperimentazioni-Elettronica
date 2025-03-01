/*
 * Custom_usart.c
 *
 *  Created on: Oct 17, 2024
 *      Author: yehan
 */

#include "Custom_usart.h"

unsigned char* data_buffer_char;
uint16_t tx_buffer_index=0;

void init_usart3(){

    USART3->CR1 |= USART_CR1_TE;
    USART3->CR1 |= USART_CR1_RE;

    USART3->CR1 &= ~USART_CR1_TXEIE;
    USART3->CR1 |= USART_CR1_RXNEIE;

    USART3->CR1 |= USART_CR1_UE;
}

void usart3_interrupt(){

	if(USART3->ISR & USART_ISR_RXNE_RXFNE){
		if(USART3->ISR & USART_ISR_TXE_TXFNF){

			char received_data = USART3->RDR;

			USART3->CR1 &= ~USART_CR1_TXEIE;

			if(received_data=='e'){

				TIM6->CR1 &= ~TIM_CR1_CEN;
				tx_buffer_index=0;
				data_buffer_char = (unsigned char*)data_buffer;

				USART3->CR1 |= USART_CR1_TXEIE;	// abilito interrupt di fine trasmissione
			}
		}
	}

	if((USART3->ISR & USART_ISR_TXE_TXFNF) && (USART3->CR1 & USART_CR1_TXEIE) && !(USART3->ISR & USART_ISR_RXNE_RXFNE)){

		if( tx_buffer_index < data_buffer_size * sizeof(data_buffer[0])){

			USART3->TDR = data_buffer_char[tx_buffer_index];
			++tx_buffer_index;
		}
		else{

			USART3->CR1 &= ~USART_CR1_TXEIE_TXFNFIE;
			tx_buffer_index=0;
			TIM6->CR1 |= TIM_CR1_CEN;
		}
	}

	USART3->ICR |= USART_ICR_ORECF; //Cancella l'overrun. Capita quando si entra in debug
	USART3->ICR |= USART_ICR_TCCF;  //Azzeramento flag interrupt trasmissione
	USART3->RQR |= USART_RQR_RXFRQ;  //Azzeramento flag interrupt ricezione
}
