/*
 * leddisp.h
 *
 *  Created on: 8 lip 2014
 *      Author: vka
 */

#ifndef LEDDISP_H_
#define LEDDISP_H_
#include "defines.h"


void showDigitOnSegment(uint8_t, uint8_t);

void showNumberOnDisplay(struct Number);

void LEDInit();

#endif /* LEDDISP_H_ */
