/*
 * main.cpp
 *
 *  Created on: 3 sie 2014
 *      Author: vka
 */

#include "SPI.h"
#define F_CPU 8000000UL
#include <util/delay.h>

int main()
{
	SPI comm;
	comm.setIOParams(&DDRB, &PORTB, 4, 7, 5, 6);
	comm.setDataOrder(false);
	comm.init();

	uint8_t pos = 0;
	uint8_t val = 1;
	int8_t dir = 1;
	while(1)
	{
		/*if(pos == 255)
			dir = -1;
		else if(pos == 0)
			dir = 1;*/
/*
		pos += dir;
		comm.sendByte(pos);
*/
		if(pos == 7)
			dir = -1;
		else if(pos == 0)
			dir = 1;
		pos += dir;
		val = 1 << pos;

		comm.sendByte(val);
		_delay_ms(50);
	}
}
