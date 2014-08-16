/*
 * main.cpp
 *
 *  Created on: 15 sie 2014
 *      Author: vka
 */
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>

#include "UART/UART.h"


volatile uint8_t value;
volatile uint8_t update;


void timerInit()
{
	TIMSK |= _BV(OCIE1A);
	TCCR1A = _BV(COM1A0) | _BV(COM1B0);

	OCR1A = F_CPU / 64UL / 36000UL;

	TCCR1B = _BV(WGM12) | _BV(CS11) | _BV(CS10);

}

int main()
{
	UART uart;

	uart.init();
	timerInit();

	DDRD &= ~(1 << PD2);
	PORTD |= 1 << PD2;

	uart.sendChar(uart.receiveChar()); //dummy
	uart.sendText((int8_t *) "Initialization successful. F_CPU: ");
	if(F_CPU == 8000000UL)
		uart.sendText((int8_t *) "8000000Hz.\n");
	else if(F_CPU == 1000000UL)
		uart.sendText((int8_t *) "1000000Hz.\n");
	else
		uart.sendText((int8_t *) "unknown.\n");

	sei();

	while(1)
	{
		if(update == 1)
		{
			if(value == 1)
				uart.sendText((int8_t*) "1");
			else
				uart.sendText((int8_t*) "0");
			update = 0;
		}
	}
}

ISR(TIMER1_COMPA_vect)
{
	update = 1;
	value = ((PIND & 1 << PD2) != 0) ? 1 : 0;

}

