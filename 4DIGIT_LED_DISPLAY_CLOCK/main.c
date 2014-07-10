/*
 * main.c
 *
 *  Created on: 8 lip 2014
 *      Author: vka
 */

#include "leddisp.h"
#include <util/delay.h>

int main()
{
	LEDInit();
	clockInit();

	Number num;

	while(1)
	{
		num = clockGetNumber();
		showNumberOnDisplay(num);

		if((CONTROLPIN & _BV(PB4)) == _BV(PB4))
			clockSet();
		if((CONTROLPIN & _BV(PB5)) == _BV(PB5))
			clockReset();
	}
}

