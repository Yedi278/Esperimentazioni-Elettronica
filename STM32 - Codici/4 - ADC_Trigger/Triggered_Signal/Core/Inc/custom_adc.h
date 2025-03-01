/*
 * custom_adc.h
 *
 *  Created on: Oct 24, 2024
 *      Author: yehan
 */

#ifndef INC_CUSTOM_ADC_H_
#define INC_CUSTOM_ADC_H_

/* INCLUDES */
#include <stdbool.h>
#include <stdint.h>
#include "stm32h743xx.h"

#define PRETRIG_VALUE 1000UL
#define TRIG_VALUE 	  2000UL


extern uint16_t data[];
extern uint16_t data_index;
extern uint16_t raw_data;

extern bool triggd;
extern bool pretriggd;

/**
 * @brief Questa funzione si occupa di configurare l'adc ed effettuare la calibrazione
 * @details La funzione accende in automatico l'adc alla fine dell'esecuzione portando ADSTART=1
 */
void adc3_init();


/**
 * @brief Questa è la funzione che contiene le azioni da eseguire durante l'interrupt dell'adc
 */
void adc3_interrupt();


#endif /* INC_CUSTOM_ADC_H_ */
