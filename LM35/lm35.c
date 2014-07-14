/*
 * lm35.c
 *
 *  Created on: 14 lip 2014
 *      Author: vka
 */

#include "lm35.h"

void LMInit()
{
	ADMUX  = _BV(REFS0) | _BV(REFS1) | LMCHANNEL;
	ADCSRA = _BV(ADEN) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
	ADCSRA |= (_BV(ADATE) | _BV(ADSC));

	temperatures.lastKnownTemp = 	0;
	temperatures.numSamples = 	0;
	temperatures.tempAccum =	0;

	sei();
}

uint16_t LMgetTemp()
{
	uint32_t val;

	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
	val = temperatures.lastKnownTemp;
	}

	//return (val * 11000UL) / (1024UL * NUMSAMPLES);4
	return val * 10UL * VREF / (NUMSAMPLES * 1024UL);
}

ISR(ADC_vect)
{
	temperatures.tempAccum += ADC;
	temperatures.numSamples++;

	if(temperatures.numSamples == NUMSAMPLES)
	{
		temperatures.lastKnownTemp = 	temperatures.tempAccum;
		temperatures.numSamples = 	0;
		temperatures.tempAccum = 	0;
	}
}
