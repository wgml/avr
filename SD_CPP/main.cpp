#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "SD.h"


int main()
{
	SD sd;
	UART uart;
	uart.init();

	sd.setUART(&uart);

	uart.receiveChar(); //dummy for waiting with start for uart comm.

	sd.init();
	while(1)
	{
		uart.sendText((int8_t*) "Infinite loop.\n");
		break;

	}

}
