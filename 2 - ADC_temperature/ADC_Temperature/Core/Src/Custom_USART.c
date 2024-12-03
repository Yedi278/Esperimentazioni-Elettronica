/*
 * Custom_USART.c
 *
 *  Created on: Dec 2, 2024
 *      Author: yehan
 */

#include "Custom_USART.h"

uint16_t tx_buff_index=0;

void usart_custom_init(){

	USART3->CR1 |= USART_CR1_TE;	// attivo trasmissione
	USART3->CR1 |= USART_CR1_RE;	// attivo ricezione

	USART3->CR1 &= ~USART_CR1_TXEIE;	// spegno interr fine trasmissione
	USART3->CR1 |= USART_CR1_RXNEIE;	// spegno interr fine ricezione

	USART3->CR1 |= USART_CR1_UE;	// abilito la periferica
}

void usart_custom_interr(){

	if(USART3->ISR & USART_ISR_RXNE_RXFNE){
		if(USART3->ISR & USART_ISR_TXE_TXFNF){

			char received_data = USART3->RDR;

			USART3->CR1 &= ~USART_CR1_TXEIE;

			if(received_data=='e'){

				TIM6->CR1 &= ~TIM_CR1_CEN;
				tx_buff_index=0;
				//data_buffer_index=0;	// resetto l'indeice dell'array

				USART3->CR1 |= USART_CR1_TXEIE;	// abilito interrupt di fine trasmissione
			}

			else if(received_data == 't'){

				USART3->TDR = ((unsigned char*)&TS_CAL_30C) [0];
				while(!(USART3->ISR & USART_ISR_TXE_TXFNF));
				USART3->TDR = ((unsigned char*)&TS_CAL_30C) [1];
				while(!(USART3->ISR & USART_ISR_TXE_TXFNF));
			}

			else if(received_data == 'T'){

				USART3->TDR = ((unsigned char*)&TS_CAL_110C) [0];
				while(!(USART3->ISR & USART_ISR_TXE_TXFNF));
				USART3->TDR = ((unsigned char*)&TS_CAL_110C) [1];
				while(!(USART3->ISR & USART_ISR_TXE_TXFNF));
			}
		}
	}

	if((USART3->ISR & USART_ISR_TXE_TXFNF) && (USART3->CR1 & USART_CR1_TXEIE) && !(USART3->ISR & USART_ISR_RXNE_RXFNE)){

		if( tx_buff_index < BUFFER_SIZE*sizeof(data_buffer[0])){

			USART3->TDR = data_buffer_char_p[tx_buff_index];
			++tx_buff_index;

		}else{

			USART3->CR1 &= ~USART_CR1_TXEIE_TXFNFIE;
			tx_buff_index=0;
			TIM6->CR1 |= TIM_CR1_CEN;
		}
	}

	USART3->ICR |= USART_ICR_ORECF; //Cancella l'overrun. Capita quando si entra in debug
	USART3->ICR |= USART_ICR_TCCF;  //Azzeramento flag interrupt trasmissione
	USART3->RQR |= USART_RQR_RXFRQ;  //Azzeramento flag interrupt ricezione
}
