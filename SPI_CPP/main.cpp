/*
 * main.cpp
 *
 *  Created on: 3 sie 2014
 *      Author: vka
 */

#include "SPI.h"
#include <util/delay.h>

int main()
{
	SPI comm;
	comm.setIOParams(&DDRB, &PORTB, 4, 7, 5, 6);
	comm.setDataOrder(false);
	comm.init();

	uint8_t pos = 0;
	int8_t dir = 0;
	while(1)
	{
		if(pos == 7)
			dir = -1;
		else if(pos == 0)
			dir = 1;

		pos += dir;
		comm.sendByte(1 << pos);

		_delay_ms(50);
	}
}
