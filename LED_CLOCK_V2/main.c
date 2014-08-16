/*
 * main.c
 *
 *  Created on: 8 lip 2014
 *      Author: vka
 */

#include "clock.h"
#include <util/delay.h>

int main()
{
	LEDInit();
	clockInit();

	while(1)
	{
		handleTick();

		/*if((CONTROLPIN & _BV(PB4)) == _BV(PB4))
			state++;*/
		if((CONTROLPIN & _BV(5)) == 0)
			clockReset();
	}
}

