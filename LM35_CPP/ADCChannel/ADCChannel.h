/*
 * ADC.h
 *
 *  Created on: 17 sie 2014
 *      Author: vka
 */

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#include "compatibility.h" //provides new, delete definitions and a bit of other necessary stuff

void interrupt();

class ADCChannel {

public:
	ADCChannel();
	virtual ~ADCChannel();

	void init(uint16_t numSamples, uint16_t numParts);

	void setChannel(uint8_t channel);

	void setVRef(uint16_t vRef); //in mV

	virtual uint32_t getValue() = 0;

	friend void interrupt();

protected:
	void handleInterrupt();

	volatile struct Container
	{
		uint32_t 	accumulator;
		uint16_t	numSamples;
		uint16_t	numParts;
		uint32_t *	lastKnownValues;
		uint16_t 	currentSample;
		uint16_t	currentPart;
		bool		firstCycle;
	} container;

	uint8_t channel;
	uint16_t vRef;
};


#endif /* ADC_H_ */
