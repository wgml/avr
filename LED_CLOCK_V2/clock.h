/*
 * timer.h
 *
 *  Created on: 10 lip 2014
 *      Author: vka
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include "leddisplay.h"
#include "clockdefines.h"


volatile struct Time currentTime;
volatile enum State state;

void clockInit();

void clockReset();

void updateTimeToDisplay();

void clockSetHour();

void clockSetMinute();

void clockUpdate();

void handleTick();

#endif /* TIMER_H_ */
