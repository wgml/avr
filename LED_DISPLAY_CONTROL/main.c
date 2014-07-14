/*
 * main.c
 *
 *  Created on: 13 lip 2014
 *      Author: Wojtek Gumuła
 */

#include "leddisplay.h"

int main()
{
	LEDInit();

	display.changed = 1;
	display.number = 233;
	display.blinkPos = 0b0000;
	display.pointPos = 0b1000;
	display.isNegative = 1;
	display.skipZeros = 1;
	display.forceFractZero = 1;
	while(1)
	{
		LEDTest();
		LEDshowOnDisplay();
	}
}
