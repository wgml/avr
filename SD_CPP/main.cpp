/*
 * main.cpp
 *
 *  Created on: 11 paź 2014
 *      Author: vka
 */

#include "UART/UART.h"

#include "SDCard.h"

int main()
{
	UART uart;
	SDCard card;

	uart.init();

	uart.receiveChar();

	uart.sendText((uint8_t *) "Program init\n");

	while(1);

}



