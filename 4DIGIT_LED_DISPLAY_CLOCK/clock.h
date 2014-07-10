/*
 * timer.h
 *
 *  Created on: 10 lip 2014
 *      Author: vka
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include "number.h"
volatile uint8_t c_hours, c_minutes, c_seconds;

void clockInit();

void clockReset();

Number clockGetNumber();

void clockSet();

#endif /* TIMER_H_ */
