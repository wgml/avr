#define F_CPU 1000000UL

#include "UART.h"
#include <util/delay.h>
#include <avr/io.h>
#define DEBUG 1
int main()
{

#ifdef DEBUG
	DDRC = 0xff;
	PORTC = 0xF0;
#endif

	UART comm;
	comm.init();

	unsigned char c;

	while(1)
	{
		c = comm.receiveChar();
#ifdef DEBUG
		PORTC = c;
#endif

		comm.sendChar(c);
		_delay_ms(10);

	}

}
