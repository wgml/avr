/*
 * main.cpp
 *
 *  Created on: 24 lip 2014
 *      Author: vka
 */

#include "LCD.h"
#include <util/delay.h>
#include <stdio.h> //sprintf :D
#include <avr/interrupt.h>

volatile uint8_t second = 0;
volatile uint8_t minute = 8;
volatile uint8_t hour = 22;
volatile bool changed = true;
int main()
{
	LCD lcd;
	lcd.setCursorVisibility(false, false);
	lcd.setFunction(false, true, true);
	lcd.init();


	TIMSK |= _BV(OCIE1A);
	TCCR1A = _BV(COM1A0) | _BV(COM1B0);

	OCR1A = F_CPU / 1024;

	TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10);
	sei();
	char buffer[16];
	while(1)
	{
		if(changed)
		{
			changed = false;
			sprintf(buffer, "Time:   %i:%i%i:%i%i", hour, (minute - minute % 10) / 10,
					minute % 10, (second - second % 10) / 10, second % 10);
			lcd.clear();
			lcd.goToPos(0, 0);
			lcd.sendText(buffer, 0);

		}
	}
	return 0;
}

ISR(TIMER1_COMPA_vect)
{

	second++;
	if(second == 60)
	{
		second = 0;
		minute++;

		if(minute == 60)
		{
			minute = 0;
			hour++;

			if(hour == 24)
				hour = 0;
		}
	}
	changed = true;
}
