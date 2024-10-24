/*
 * Custom_usart.c
 *
 *  Created on: Oct 17, 2024
 *      Author: yehan
 */

#include "Custom_usart.h"

unsigned char* converted_buffer_pointer;
int data_index=0;

void init_usart3(){

    USART3->CR1 |= USART_CR1_TE;
    USART3->CR1 |= USART_CR1_RE;

    //USART3->CR1 ^= USART_CR1_TXEIE;
    USART3->CR1 |= USART_CR1_RXNEIE;

    USART3->CR1 |= USART_CR1_UE;

}

void usart3_interrupt(){

	extern uint16_t temp_buffer[];
	extern data_index;

	if(USART3->ISR & USART_ISR_RXNE_RXFNE){
		if(USART3->ISR & USART_ISR_TXE_TXFNF){

			char received_data = USART3->RDR;

			USART3->CR1 ^= USART_CR1_TXEIE;

			if(received_data=='e'){
                data_index=0;

                converted_buffer_pointer = (unsigned char*)temp_buffer;
				// FUNC() GENERA VETTORE DI DATI SE NECESSARIO
                //genera_vett_esp(data_buffer, (int)SIZE_OF_BUFF(data_buffer), 0, 0);
                USART3->CR1 |= USART_CR1_TXEIE;
			}
		}
	}

	if((USART3->ISR & USART_ISR_TXE_TXFNF) && (USART3->CR1 & USART_CR1_TXEIE) && !(USART3->ISR & USART_ISR_RXNE_RXFNE)){

        if( data_index < 1000 * sizeof(temp_buffer[0])){

            USART3->TDR = converted_buffer_pointer[data_index];
            ++data_index;
        }else{
            USART3->CR1 ^= USART_CR1_TXEIE_TXFNFIE;
        }
	}

	USART3->ICR |= USART_ICR_ORECF; //Cancella l'overrun. Capita quando si entra in debug
	USART3->ICR |= USART_ICR_TCCF;  //Azzeramento flag interrupt trasmissione
	USART3->RQR |= USART_RQR_RXFRQ;  //Azzeramento flag interrupt ricezione

}
