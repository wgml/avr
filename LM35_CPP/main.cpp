/*
 * main.cpp
 *
 *  Created on: 17 sie 2014
 *      Author: vka
 */
#define F_CPU 8000000UL

#include "LM35.h"
#include "UART/UART.h"
#include <util/delay.h>
#include <stdio.h>
int main()
{
	LM35 term;
	term.setChannel(0b0000);
	term.setVRef(2560);

	UART comm;
	comm.init();
	char c = comm.receiveChar();
	comm.sendChar(c);
	term.init(30, 100);

	comm.sendText((int8_t*) "initialized\n");

	char buffer[30];
	while(1)
	{
		sprintf(buffer, "Current value * 100: %i\r", (int16_t)term.getValue());

		comm.sendText((int8_t *) buffer);
		_delay_ms(10);
	}
}


