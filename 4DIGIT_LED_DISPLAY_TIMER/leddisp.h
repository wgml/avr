/*
 * leddisp.h
 *
 *  Created on: 8 lip 2014
 *      Author: vka
 */

#ifndef LEDDISP_H_
#define LEDDISP_H_
#include "defines.h"
#include "timer.h"

void showCharOnSegment(uint8_t, uint8_t);

void showNumberOnDisplay(Number);

void LEDInit();

void LEDTest();

void LEDReset();

void LEDsetError(uint8_t);

#endif /* LEDDISP_H_ */
