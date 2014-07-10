/*
 * timers.c
 *
 *  Created on: 10 lip 2014
 *      Author: vka
 */

#include <avr/interrupt.h>
#include <avr/io.h>

void timerInit()
{
	TIMSK |= _BV(OCIE1A);
	TCCR1A = _BV(COM1A0) | _BV(COM1B0);

	OCR1A = F_CPU / 10240;

	TCCR1B = _BV(WGM12) | _BV(CS12) | _BV(CS10);

	DDRB |= _BV(PB0) | _BV(PB1);
}

ISR(TIMER1_COMPA_vect)
{
	static uint8_t LED = 0b01;
	LED ^= 0b11;

	PORTB = (PORTB & 0b11111100) | LED;
}

int main()
{
	timerInit();

	sei();

	while(1);
}


/* normal
void timerInit()
{
	TIMSK = _BV(TOIE1);
	TCCR1B |= _BV(CS10);

	DDRB |= _BV(PB0) | _BV(PB1);
}

ISR(TIMER1_OVF_vect)
{
	static uint8_t LED = 0b01;
	LED ^= 0b11;

	PORTB = (PORTB & 0b11111100) | LED;
}

int main()
{
	timerInit();

	sei();

	while(1);
}
*/
