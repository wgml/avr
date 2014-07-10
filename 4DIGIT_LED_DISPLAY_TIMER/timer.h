/*
 * timer.h
 *
 *  Created on: 10 lip 2014
 *      Author: vka
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>

volatile uint16_t t_count;
volatile uint8_t t_enable;

void timerInit();

void timerReset();

void timerSwitchEnabled();

#endif /* TIMER_H_ */
