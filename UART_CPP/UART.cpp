/*
 * UART.cpp
 *
 *  Created on: 27 lip 2014
 *      Author: vka
 */

#include "UART.h"
//#include <avr/io.h> //todo wtf? not working without that

UART::UART() {
	// TODO Auto-generated constructor stub
	bufferSize = 0;
	this->buffer = NULL;
}

UART::~UART()
{
	if(this->buffer)
	{
		free(this->buffer);
		this->buffer = NULL;
	}
}

void UART::initBuffer(uint8_t size)
{
	if(this->buffer)
	{
		this->bufferSize = 0;
		free(this->buffer);
		this->buffer = NULL;
	}

	this->bufferSize = size;
	this->buffer = (uint8_t *) malloc(sizeof(uint8_t) * this->bufferSize);

	if(!this->buffer)
		this->~UART();
}

uint8_t UART::getBufferSize()
{
	return this->bufferSize;
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

uint8_t UART::receiveChar()
{
	while(!(UCSRA & _BV(RXC))); //wait for transmition
	return UDR & ~0x80;
}

void UART::sendChar(uint8_t c)
{
	while(!(UCSRA & _BV(UDRE)));
	UDR = c;
}

uint8_t * UART::receiveText(uint8_t length, uint8_t terminate)
{
	/*
	 * gets chars from UART and puts
	 * them into buffer.
	 * Return ptr to buffer
	 * */

	if(this->bufferSize < length || !this->buffer)
		this->initBuffer(length);

	uint8_t l = 0;
	while((l < this->bufferSize) && ((this->buffer[l++] = this->receiveChar()) != terminate));
	this->buffer[l] = '\0';
	return this->buffer;
}

void UART::sendText(const uint8_t * txt)
{
	while(*txt != '\0')
		this->sendChar(*txt++);
}

uint8_t * UART::getBufferPointer()
{
	return this->buffer;
}
