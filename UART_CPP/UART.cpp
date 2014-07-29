/*
 * UART.cpp
 *
 *  Created on: 27 lip 2014
 *      Author: vka
 */

#include "UART.h"


UART::UART() {
	// TODO Auto-generated constructor stub

}

void UART::init()
{

	this->init_9600();

	UCSRC |= _BV(URSEL) | /*_BV(USBS) |*/ _BV(UCSZ1) | _BV(UCSZ0); //8-bit data, 2-bit stop

	UCSRB |= _BV(RXEN) | _BV(TXEN); //receive & send enabled
}

void UART::init_9600()
{
	#define BAUD 9600
	#define BAUD_PRESCALE (((F_CPU / (BAUD * 16UL))) - 1)
	//#include <util/setbaud.h>

	UBRRH = BAUD_PRESCALE >> 8;
	UBRRL = BAUD_PRESCALE;
/*
	#if USE_2X
		UCSRA |= (1 << U2X);
	#else
		UCSRA &= ~(1 << U2X);
	#endif*/
}

uint8_t UART::receive()
{
	while(!(UCSRA & _BV(RXC))); //wait for transmition
	return UDR;
}

void UART::send(uint8_t c)
{
	while(!(UCSRA & _BV(UDRE)));
	UDR = c;
}

