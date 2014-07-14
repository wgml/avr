/*
 * lm35.h
 *
 *  Created on: 14 lip 2014
 *      Author: vka
 */

#ifndef LM35_H_
#define LM35_H_

#define NUMSAMPLES	30ULL
#define NUMPARTS	100ULL
#define	LMCHANNEL	0b0000
#define LMPIN		0b00000001
#define VREF		2560ULL		//in mV
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include "leddisplay.h"

struct TempContainer
{
	uint32_t 	tempAccum;
	uint16_t	numSamples;
	uint16_t	numParts;
	uint32_t	lastKnownTemp[NUMPARTS];

	uint8_t	firstCycle;
};

static struct TempContainer temperatures;

void LMInit();

uint16_t LMgetTemp();

#endif /* LM35_H_ */
