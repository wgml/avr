/*
 * main.cpp
 *
 *  Created on: 24 lip 2014
 *      Author: vka
 */

#include "LCD.h"
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t second = 0;
volatile uint8_t minute = 8;
volatile uint8_t hour = 22;
volatile bool changed = true;
int main()
{


	LCD lcd;
	lcd.setCursorVisibility(true, false);
	lcd.setFunction(false, true, true);
	lcd.init();

	TIMSK |= _BV(OCIE1A);
	TCCR1A = _BV(COM1A0) | _BV(COM1B0);

	OCR1A = F_CPU / 1024;

	TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10);

	sei();

	lcd.sendInt(F_CPU);
	while(1)
	{
		if(changed)
		{
			changed = false;

			lcd.clear();
			lcd.sendText("Time:   ");
			lcd.sendInt(hour);
			lcd.sendChar(':');
			lcd.sendDigit((minute - minute % 10) / 10);
			lcd.sendDigit(minute % 10);
			lcd.sendChar(':');
			lcd.sendDigit((second - second % 10) / 10);
			lcd.sendDigit(second % 10);
			lcd.goToPos(1, 0);
			lcd.sendText("Freq:   ");
			lcd.sendInt(F_CPU);

		}

		/*lcd.clear();
		lcd.sendText("Testing...");
		lcd.goToPos(1, 0);
		lcd.sendInt(-218642235);
		lcd.sendChar(' ');
		lcd.sendInt(-11);
		lcd.sendChar(' ');
		lcd.sendInt(0);
		lcd.sendChar('z');
		lcd.sendSpecialChar(1);

		_delay_ms(1000);*/
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

