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

	temperatures.numParts = 	0;
	temperatures.numSamples = 	0;
	temperatures.tempAccum =	0;
	temperatures.firstCycle =	1;

	sei();
}

uint16_t LMgetTemp()
{
	uint32_t vals[NUMPARTS];
	uint64_t sumVals = 0;
	uint8_t firstCycle = temperatures.firstCycle;
	uint16_t sumParts = NUMPARTS;
	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		for(uint16_t part = 0; part < NUMPARTS; part++)
			vals[part] = temperatures.lastKnownTemp[part];

		if(firstCycle == 1)
			sumParts = temperatures.numParts;
	}
	for(uint16_t part = 0; part < sumParts; part++)
		sumVals += vals[part];

	return sumVals * 10UL * VREF / (NUMSAMPLES * sumParts * 1024UL);
}

ISR(ADC_vect)
{
	temperatures.tempAccum += ADC;
	temperatures.numSamples++;

	if(temperatures.numSamples == NUMSAMPLES)
	{
		temperatures.lastKnownTemp[temperatures.numParts++] = temperatures.tempAccum;
		temperatures.numSamples = 	0;
		temperatures.tempAccum = 	0;

		if(temperatures.numParts == NUMPARTS)
		{
			temperatures.numParts = 0;

			if(temperatures.firstCycle == 1)
				temperatures.firstCycle = 0;
		}
	}
}
