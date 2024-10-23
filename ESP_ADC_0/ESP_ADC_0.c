/*
 * ESP_ADC.c
 *
 *  Created on: Nov 6, 2023
 *      Author: utente
 */


#include "ESP_ADC_0.h"



//Passo 1:   IdeCUBE

//selezionare ADC3. Per le prime misure la freqeunza non ha importanza
//Impostare i 2 ingressi VSENSE (forse questa non la misuriamo) e VREFINT

//Queste sono le operazioni che dobbiamo fare, magari con una funzione, nel main(), prima del while(1) (va fatta una sola volta)
void ESPE_ADC_0_init(void) {//Inizializzazione ADC
//Passo 2: impostare gli ingressi per la misura

//1)
//selezionaimao gli ingressi ed il numero di ingressi mediante il registro SQR1


//2)
//Impostiamo anche PCSEL: dobbiamo indicare quali canali legggiamo affinchè si impsti la velocità massima degli ingressi


//3)
//nel CR vanno impostati DEEPPWD e ADVREGEN

//4)
//Calibrare l'ADC, agendo nel CR con i flag ADCALDIF, ADCALLIN, ADEN e ADCAL

//5)
//Accendiamo l'ADC, questo non significa effettuare misure, ADRDY nell'ISR e ADEN nel CR

//6)
//Abilitare l'interrupt, EOCIE nell'IER  (sarà l'EOC nell'ISR il flag di interrupt)

//7)
//Eventialmente inseire un ritardo per la lettura del canale dopo la connessione in SMPR1 e SMPR2

//8)
//Per potere leggere la temperatura e la tensione occorre abilitare i flag 	TSEN e VREFEN nel CCR


//9)
//Nel registro CRGR indicare che misura si vuole considerare, CONT: single o continua, oppure con trigger per esempio con timer, consigliato TIM6.
//oppure si può usare il trigger sw con ADSTART nel CR, consigliato all'inizio.

}//Fine inizializzazione ADC

