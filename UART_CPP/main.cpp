#include "LCD/hd44780/hd44780.c"
#include "LCD/LCD.h"

#include "UART.h"

#define DEBUG 0

int main()
{

	if(DEBUG)
	{
		DDRC = 0xff;
		PORTC = 0;
	}

	LCD lcd;
	lcd.setCursorVisibility(true, true);
	lcd.setFunction(false, true, true);

	lcd.init();
	lcd.clear();
	lcd.goToPos(0, 0);

	lcd.sendText((const uint8_t *) "Receiving...\n");

	_delay_ms(1000);

	lcd.clear();
	lcd.goToPos(0, 0);

	UART comm;
	comm.init();

	//unsigned char c;

	while(1)
	{
		lcd.sendText(comm.receiveText(1, '\n'));
		comm.sendText((const uint8_t *) "received one char");
		_delay_ms(1000);

	}

}
