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
	timerInit();

	Number num = {0, 2, 0, 1};
	while(1)
	{
		num.num = t_count;
		showNumberOnDisplay(num);

		if((CONTROLPIN & _BV(PB4)) == _BV(PB4))
			timerSwitchEnabled();

		if((CONTROLPIN & _BV(PB5)) == _BV(PB5))
			timerReset();
	}
}

