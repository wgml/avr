/*
 * main.c
 *
 *  Created on: 13 lip 2014
 *      Author: Wojtek Gumuła
 */

#include "leddisplay.h"
#include <util/delay.h>

int main()
{
	LEDInit();

	display.changed = 0;
	LEDTest();

	while(1)
	{
		LEDshowOnDisplay();
	}
}
