/*
 * timer.c
 *
 *  Created on: 10 lip 2014
 *      Author: vka
 */

#include "clock.h"
#include <avr/interrupt.h>
#include <util/delay.h>

void clockInit()
{
	sei();

	TIMSK |= _BV(OCIE1A);
	TCCR1A = _BV(COM1A0) | _BV(COM1B0);

	OCR1A = F_CPU / 10240;

	TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10);

	currentTime.hour = 11;
	currentTime.minute = 59;
	currentTime.second = 50;
	currentTime.ms = 0;

	display.number = 0;
	display.isNegative = 0;
	display.skipZeros = 0;
	display.pointPos = 0b0100;
	display.blinkPos = 0b0000;
	display.changed = 1;
	display.forceFractZero = 0;

	state = CLOCK;
}

void clockReset()
{
	currentTime.hour = 11;
	currentTime.minute = 59;
	currentTime.second = 50;
	currentTime.ms = 0;

	state = CLOCK;
}

void updateTimeToDisplay()
{
	/*
	 * updates display variable value
	 */
	if(currentTime.changed == 0)
		return;

	display.number = 0;

	display.number = 100 * (currentTime.hour - (currentTime.hour % 10));

	display.number += 100 * (currentTime.hour % 10);

	display.number += currentTime.minute - (currentTime.minute % 10);

	display.number += currentTime.minute % 10;

	if((currentTime.second % 2) == 1)
		display.pointPos = 0b0100;
	else
		display.pointPos = 0b0000;

	display.changed = 1;

}

void clockSetHour()
{ //todo
	//currentTime.blinkSeg = 0b1100;

	uint8_t ms = (currentTime.ms + 5) % 10;
	while(currentTime.ms != ms)
		clockUpdate();

	//adjusting hour
	while(!((CONTROLPIN & _BV(PB4)) == _BV(PB4)))
	{
		if((CONTROLPIN & _BV(PB5)) == _BV(PB5))
		{
			currentTime.hour = (currentTime.hour + 1) % 24;
			ms = (currentTime.ms + 5) % 10;
			while(currentTime.ms != ms)
				clockUpdate();
		}
		clockUpdate();
	}
	state = CLOCK;

	//currentTime.blinkSeg = 0b0000;
	ms = (currentTime.ms + 5) % 10;

	while(currentTime.ms != ms)
		clockUpdate();
}

void clockSetMinute()
{ //todo
	//currentTime.blinkSeg = 0b0011;

	uint8_t ms = (currentTime.ms + 5) % 10;
	while(currentTime.ms != ms)
		clockUpdate();

	//adjusting minute
	while(!((CONTROLPIN & _BV(PB4)) == _BV(PB4)))
	{
		if((CONTROLPIN & _BV(PB5)) == _BV(PB5))
		{
			ms = (currentTime.ms + 5) % 10;
			while(currentTime.ms != ms && !((CONTROLPIN & _BV(PB4)) == _BV(PB4)))
				clockUpdate();

			currentTime.minute = (currentTime.minute + 1) % 60;
		}
		clockUpdate();
	}

	//currentTime.blinkSeg = 0b0000;
	ms = (currentTime.ms + 5) % 10;

	while(currentTime.ms != ms)
		clockUpdate();
}

void clockUpdate()
{
	updateTimeToDisplay();
	LEDshowOnDisplay();

}

void handleTick()
{
	switch(state)
	{
	case CLOCK:
		clockUpdate();
		break;
	case SET_HOUR:
		clockSetHour();
		break;
	case SET_MINUTE:
		clockSetMinute();
		break;
	default:
		state = CLOCK;
		clockUpdate();
		break;
	}
}
ISR(TIMER1_COMPA_vect)
{
	currentTime.ms++;

	if(currentTime.ms == 10)
	{
		currentTime.ms = 0;
		currentTime.second++;
		currentTime.changed = 1;

		if(currentTime.second == 60)
		{
			currentTime.second = 0;
			currentTime.minute++;

			if(currentTime.minute == 60)
			{
				currentTime.minute = 0;
				currentTime.hour++;

				if(currentTime.hour == 24)
					currentTime.hour = 0;
			}
		}
	}
}

