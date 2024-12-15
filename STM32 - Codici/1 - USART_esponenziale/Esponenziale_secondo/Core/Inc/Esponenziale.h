/*
 * Esponenziale.h
 *
 *  Created on: Oct 10, 2024
 *      Author: yehan
 */

#ifndef INC_ESPONENZIALE_H_
#define INC_ESPONENZIALE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void init_exp_buff(uint16_t* buff, int length);

void genera_vett_esp(uint16_t* buff, int length, double tau1, double tau2);

#endif /* INC_ESPONENZIALE_H_ */
