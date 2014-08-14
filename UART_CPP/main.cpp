#define F_CPU 8000000UL

#include "UART.h"
#include <util/delay.h>
#include <avr/io.h>
#define DEBUG 1
int main()
{

#ifdef DEBUG
	DDRC = 0xff;
	PORTC = 0xff;
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
