/*
 * LM35.cpp
 *
 *  Created on: 17 sie 2014
 *      Author: vka
 */

#include "LM35.h"

void interrupt()
{
	handle->handleInterrupt();
}

LM35::LM35()
	: ADCChannel()
{
	handle = this;
}

uint32_t LM35::getValue()
{
	uint32_t vals[this->container.numParts];
	uint64_t sumVals = 0;
	uint8_t firstCycle = this->container.firstCycle;
	uint16_t sumParts = this->container.numParts;

	ATOMIC_BLOCK(ATOMIC_FORCEON)
	{
		for(uint16_t part = 0; part < this->container.numParts; part++)
			vals[part] = this->container.lastKnownValues[part];

		if(firstCycle == 1)
			sumParts = this->container.currentPart;
	}

	for(uint16_t part = 0; part < sumParts; part++)
		sumVals += vals[part];

	return sumVals * 10UL * this->vRef / (this->container.numSamples * sumParts * 1024UL);
}
