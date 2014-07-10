/*
 * timer.c
 *
 *  Created on: 10 lip 2014
 *      Author: vka
 */

#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
void timerInit()
{
	sei();

	TIMSK |= _BV(OCIE1A);
	TCCR1A = _BV(COM1A0) | _BV(COM1B0);

	OCR1A = F_CPU / 102400;

	TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10);

	t_count = 0;
	t_enable = 0;
}

void timerReset()
{
	t_count = 0;
}

void timerSwitchEnabled()
{
	t_enable = 1 - t_enable;
	_delay_ms(100); //so we won't start and stop it continuously

}

ISR(TIMER1_COMPA_vect)
{
	if(t_enable == 1)
		t_count++;

	if(t_count > 9999)
		t_count = 0;
}

