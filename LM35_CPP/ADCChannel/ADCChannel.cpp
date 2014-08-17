/*
 * ADC.cpp
 *
 *  Created on: 17 sie 2014
 *      Author: vka
 */

#include "ADCChannel.h"

ADCChannel::ADCChannel()
{
	this->container.lastKnownValues = 0;
	this->channel = 0;
	this->vRef = 0;
}

ADCChannel::~ADCChannel()
{
	if(this->container.lastKnownValues)
		delete this->container.lastKnownValues;
}

void ADCChannel::setChannel(uint8_t channel)
{
	this->channel = channel;
}

void ADCChannel::setVRef(uint16_t vRef)
{
	this->vRef = vRef;
}

void ADCChannel::init(uint16_t numSamples, uint16_t numParts)
{
	this->container.numParts = numParts;
	this->container.numSamples = numSamples;

	this->container.lastKnownValues = new uint32_t[numParts];
	if(this->container.lastKnownValues == 0)
		return; //bad error

	this->container.firstCycle = true;
	this->container.accumulator = 0;
	this->container.currentPart = 0;
	this->container.currentSample = 0;

	ADMUX  = _BV(REFS0) | _BV(REFS1) | this->channel;
	ADCSRA = _BV(ADEN) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
	ADCSRA |= (_BV(ADATE) | _BV(ADSC));

	sei();
}

void ADCChannel::handleInterrupt()
{
	this->container.accumulator += ADC;
	this->container.currentSample++;

	if(this->container.currentSample == this->container.numSamples)
	{
		this->container.lastKnownValues[this->container.currentPart++] = this->container.accumulator;
		this->container.currentSample = 0;
		this->container.accumulator = 0;

		if(this->container.currentPart == this->container.numParts)
		{
			this->container.currentPart = 0;

			this->container.firstCycle = false;
		}
	}
}

ISR(ADC_vect)
{
	interrupt();
}
