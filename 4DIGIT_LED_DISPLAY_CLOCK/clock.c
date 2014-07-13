/*
 * timer.c
 *
 *  Created on: 10 lip 2014
 *      Author: vka
 */

#include "clock.h"
#include "defines.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void clockInit()
{
	sei();

	TIMSK |= _BV(OCIE1A);
	TCCR1A = _BV(COM1A0) | _BV(COM1B0);

	OCR1A = F_CPU / 1024;

	TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10);

	c_hours = 0;
	c_minutes = 0;
	c_seconds = 0;
}

void clockReset()
{
	c_hours = 0;
	c_minutes = 0;
	c_seconds = 0;
}

Number clockGetNumber()
{
	Number num;
	num.num = 100 * c_hours + c_minutes;
	num.minus = 0;
	num.skipZeros = 0;
	if(c_seconds % 2 == 1)
		num.pointPos = 2;
	else
		num.pointPos = 0;

	return num;
}

void clockSet()
{
	//seconds are not being set

	uint8_t t_hours = c_hours;
	uint8_t t_minutes = c_minutes;

	_delay_ms(500);
	//adjusting hour
	while(!((CONTROLPIN & _BV(PB4)) == _BV(PB4)))
	{
		if((CONTROLPIN & _BV(PB5)) == _BV(PB5))
		{
			_delay_ms(500); //safety
			t_hours = (t_hours + 1) % 24;
		}
	}

	_delay_ms(500);
	//adjusting minute
	while(!((CONTROLPIN & _BV(PB4)) == _BV(PB4)))
	{
		if((CONTROLPIN & _BV(PB5)) == _BV(PB5))
		{
			_delay_ms(500); //safety
			t_minutes = (t_minutes + 1) % 24;
		}
	}

	//updating time
	c_hours = t_hours;
	c_minutes = t_minutes;

	_delay_ms(500); //safety
}

ISR(TIMER1_COMPA_vect)
{
	c_seconds++;

	if(c_seconds == 60)
	{
		c_seconds = 0;
		c_minutes++;

		if(c_minutes == 60)
		{
			c_minutes = 0;
			c_hours++;

			if(c_hours == 24)
				c_hours = 0;
		}
	}
}

