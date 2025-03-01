/*
 * Custom_usart.c
 *
 *  Created on: Oct 17, 2024
 *      Author: yehan
 */

#include "Custom_usart.h"

uint16_t data_buffer[1000];
unsigned char* data_buffer_8bit = (unsigned char*)data_buffer;
int data_index=0;

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

			if(received_data=='e'){
                data_index=0;

				// FUNC() GENERA VETTORE DI DATI SE NECESSARIO
                genera_vett_esp(data_buffer, (int)SIZE_OF_BUFF(data_buffer), 0, 0);
                
                USART3->CR1 |= USART_CR1_TXEIE;
			}
		}
	}

	if((USART3->ISR & USART_ISR_TXE_TXFNF) && (USART3->CR1 & USART_CR1_TXEIE) && !(USART3->ISR & USART_ISR_RXNE_RXFNE)){

        if(data_index < 1000 * sizeof(data_buffer[0])){

            USART3->TDR = data_buffer_8bit[data_index];
            ++data_index;
        }else{
            USART3->CR1 &= ~USART_CR1_TXEIE_TXFNFIE;
        }
	}

	USART3->ICR |= USART_ICR_ORECF; //Cancella l'overrun. Capita quando si entra in debug
	USART3->ICR |= USART_ICR_TCCF;  //Azzeramento flag interrupt trasmissione
	USART3->RQR |= USART_RQR_RXFRQ;  //Azzeramento flag interrupt ricezione
}
