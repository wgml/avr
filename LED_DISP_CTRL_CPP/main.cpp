#include <avr/io.h>
#include <avr/interrupt.h> //just for timer
#include "LEDDisplay.h"
#define F_CPU 1000000

//timer
volatile uint16_t val;

int main()
{
	//usage:

	//call full constructor
	LEDDisplay led(&DDRB, &PORTB, &DDRC, &PORTC, 50, true);

	/*
	 * or default constructor and set proper values
	 *
	 * LEDDisplay led;
	 * led.setControlPort(&DDRB, &PORTB);
	 * led.setDisplayPort(&DDRC, &PORTC);
	 * led.setDisplayMode(true);
	 * led.setBrightness(50);
	 */

	//call init() function to set ports state.
	led.init();

	/*
	 * set init values od display struct. (see LEDDisplay.h for more).
	 */
	led.display.number = 0;
	led.display.forceFractZero = false;
	led.display.pointPos = 0b0010;
	led.display.changed = true;
	led.display.skipZeros = false;


	//timer stuff
	val = 0;

	TIMSK |= _BV(OCIE1A);
	TCCR1A = _BV(COM1A0) | _BV(COM1B0);
	OCR1A = F_CPU / 10240;
	TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10);
	sei();
	//end of timer stuff

	while(1)
	{
		if(val != led.display.number)
		{
			led.display.number = val;
			led.display.changed = true;
		}
		led.update();
	}
}


//timer stuff
ISR(TIMER1_COMPA_vect)
{
	val++;
	val %= 10000;
}
