/*
 * main.c
 *
 *  Created on: 8 lip 2014
 *      Author: vka
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

//used port A, pins 1-3 as outputs. Pins 4-5 are inputs.

bool checkIter();
bool checkSwitch();

int main()
{
	DDRA |= 0b1110;
	PORTA |= _BV(PA4) | _BV(PA5);
	uint8_t state = 0;

	while(1)
	{
		if(checkIter())
		{
			PORTA ^= 1 << (++state);
			state %= 3;
		}
		if(checkSwitch())
			PORTA ^= 0b1110;
		_delay_ms(100);
	}
}

bool checkIter()
{
	if(((PINA >> 4) & 0x01) == 0)
	{
		_delay_ms(30);
		if(((PINA >> 4) & 0x01) == 0)
			return true;
	}
	return false;
}

bool checkSwitch()
{
	if(((PINA >> 5) & 0x01) == 0)
	{
		_delay_ms(30);
		if(((PINA >> 5) & 0x01) == 0)
			return true;
	}
	return false;
}


