/*
 * Custom_usart.c
 *
 *  Created on: Oct 17, 2024
 *      Author: yehan
 */

#include <custom_usart.h>

unsigned char* buffer_char;
uint16_t buffer_read_idx=0;

void usart3_init(){

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

				buffer_read_idx=0;
                buffer_char = (unsigned char *)data;

                USART3->CR1 |= USART_CR1_TXEIE;
			}
		}
	}

	if((USART3->ISR & USART_ISR_TXE_TXFNF) && (USART3->CR1 & USART_CR1_TXEIE) && !(USART3->ISR & USART_ISR_RXNE_RXFNE)){

		if(buffer_read_idx < 1000 * sizeof(data[0])){

            USART3->TDR = buffer_char[buffer_read_idx];
            ++buffer_read_idx;

        }else{
        	TIM6->CR1 |= TIM_CR1_CEN;
            USART3->CR1 &= ~USART_CR1_TXEIE_TXFNFIE;
        }
	}

	USART3->ICR |= USART_ICR_ORECF; //Cancella l'overrun. Capita quando si entra in debug
	USART3->ICR |= USART_ICR_TCCF;  //Azzeramento flag interrupt trasmissione
	USART3->RQR |= USART_RQR_RXFRQ;  //Azzeramento flag interrupt ricezione
}






