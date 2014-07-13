/*
 * leddisplay.h
 *
 *  Created on: 13 lip 2014
 *      Author: Wojtek Gumuła
 */

#ifndef LEDDISPLAY_H_
#define LEDDISPLAY_H_

#include "defines.h"

static volatile uint8_t			_segments[4];
static const uint8_t DIGITS[10] = {	DIG0, 	DIG1, 	DIG2, 	DIG3,	DIG4,
					DIG5, 	DIG6, 	DIG7, 	DIG8, 	DIG9
					};
volatile struct Display 		display;

void LEDInit();

void LEDTest();

void LEDshowOnDisplay();

static void _LEDupdateSegments();

static void _LEDsetErrorMessage(uint8_t);

static void _LEDsetValueOnSegment(uint8_t, uint8_t);

#endif /* LEDDISPLAY_H_ */
