/*
 * Esponenziale.c
 *
 *  Created on: Oct 10, 2024
 *      Author: yehan
 */
#include "Esponenziale.h"


void init_exp_buff(uint16_t* buff, int length){
	for(int i=0; i<length; ++i)
		buff[i] = 0;
}

void genera_vett_esp(uint16_t* buff, int length, double tau1, double tau2){

	init_exp_buff(buff,length);	// Vengono settate tutte le entreate a 0

	// Allocazione di memoria per i due esponenziali
	uint16_t* buff_1 = (uint16_t*)malloc(sizeof(uint16_t)*length);
	uint16_t* buff_2 = (uint16_t*)malloc(sizeof(uint16_t)*length);

	// Settaggio delle costanti di tempo caratteristico
	uint16_t const_1 = 957;
	uint16_t const_2 = 926;

	// Settaggio valori iniziali
	buff_1[0] = 25000;
	buff_2[0] = 25000;

	for(int i=1; i<length; ++i){
		buff_1[i] = (buff_1[i-1] * const_1) >> 10;
		buff_2[i] = (buff_2[i-1] * const_2) >> 10;
	}

	for(int i=0; i<length; ++i)
		buff[i] = buff_1[i]-buff_2[i];

	free(buff_1);
	free(buff_2);
}
