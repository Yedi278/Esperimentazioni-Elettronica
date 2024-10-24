/*
 * Custom_usart.c
 *
 *  Created on: Oct 17, 2024
 *      Author: yehan
 */

#include <custom_usart.h>

unsigned char* data_buffer_char = 0;
int data_buffer_read_index=0;

void usart3_init(){

    USART3->CR1 |= USART_CR1_TE;
    USART3->CR1 |= USART_CR1_RE;

    USART3->CR1 &= ~USART_CR1_TXEIE;
    USART3->CR1 |= USART_CR1_RXNEIE;

    USART3->CR1 |= USART_CR1_UE;
}

void usart3_interrupt(){

	extern uint16_t data_buffer[1000];
	extern bool reading;

	if(USART3->ISR & USART_ISR_RXNE_RXFNE){
		if(USART3->ISR & USART_ISR_TXE_TXFNF){

			char received_data = USART3->RDR;

			USART3->CR1 &= ~USART_CR1_TXEIE;

			if(received_data=='?'){
				data_buffer_read_index=0;
				reading = true;
                data_buffer_char = (unsigned char *)data_buffer;

                USART3->CR1 |= USART_CR1_TXEIE;
			}
		}
	}

	if((USART3->ISR & USART_ISR_TXE_TXFNF) && (USART3->CR1 & USART_CR1_TXEIE) && !(USART3->ISR & USART_ISR_RXNE_RXFNE)){

		if(data_buffer_read_index < sizeof(data_buffer)){

            USART3->TDR = data_buffer_char[data_buffer_read_index];
            ++data_buffer_read_index;
        }else{
            USART3->CR1 &= ~USART_CR1_TXEIE_TXFNFIE;
            reading = false;
        }
	}

	USART3->ICR |= USART_ICR_ORECF; //Cancella l'overrun. Capita quando si entra in debug
	USART3->ICR |= USART_ICR_TCCF;  //Azzeramento flag interrupt trasmissione
	USART3->RQR |= USART_RQR_RXFRQ;  //Azzeramento flag interrupt ricezione
}







