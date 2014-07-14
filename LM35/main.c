/*
 * main.c
 *
 *  Created on: 14 lip 2014
 *      Author: Wojtek Gumuła
 */

#include "lm35.h"

int main()
{
	LMInit();
	LEDInit();
	uint16_t temperature = 8888;

	display.blinkPos = 0b0000;
	display.changed = 1;
	display.forceFractZero = 0;
	display.isNegative = 0;
	display.number = temperature;
	display.pointPos = 0b0100;
	display.skipZeros = 0;

	while(1)
	{
		temperature = LMgetTemp();
		if(temperature != display.number)
		{
			display.number = temperature;
			display.changed = 1;
		}

		ATOMIC_BLOCK(ATOMIC_FORCEON)
		{
			LEDshowOnDisplay();
		}
	}
}
