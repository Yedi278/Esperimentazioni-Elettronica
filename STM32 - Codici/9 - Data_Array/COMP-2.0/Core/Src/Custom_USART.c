/*
 * Custom_USART.c
 *
 *  Created on: Dec 6, 2024
 *      Author: yehan
 */

#include "Custom_USART.h"

void USART_custom_init(){

	USART3->CR1 |= USART_CR1_TE;
	USART3->CR1 |= USART_CR1_RE;

	USART3->CR1 &= ~USART_CR1_TXEIE;
	USART3->CR1 |= USART_CR1_RXNEIE;

	USART3->CR1 |= USART_CR1_UE;
}

void USART_custom_interrupt(){

	char data = USART3->RDR;

	if(data == '?'){
		if((TIM7->CR1 & TIM_CR1_CEN) == 0){
			TIM7->CR1 |= TIM_CR1_CEN;
		}
	}

	USART3->ICR |= USART_ICR_ORECF;  //Cancella l'overrun. Capita quando si entra in debug
	USART3->ICR |= USART_ICR_TCCF;   //Azzeramento flag interrupt trasmissione
	USART3->RQR |= USART_RQR_RXFRQ;  //Azzeramento flag interrupt ricezione
}
