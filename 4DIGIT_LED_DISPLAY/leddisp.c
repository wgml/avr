/*
 * leddisp.c
 *
 *  Created on: 8 lip 2014
 *      Author: vka
 */

#include "leddisp.h"

const uint8_t DIGITS[13] = {	DIG0, 	DIG1, 	DIG2, 	DIG3,
								DIG4,	DIG5, 	DIG6, 	DIG7,
								DIG8, 	DIG9,	DPOINT, DMINUS,
								DOFF	};
void showDigitOnSegment(uint8_t digit, uint8_t seg)
{
	CONTROLPORT = ~(1 << (seg - 1));
	LEDPORT = digit;
}

void showNumberOnDisplay(struct Number num)
{
	uint8_t digits[4], digit;
	for(uint8_t i = 0; i < 4; i++)
	{
		digits[3 - i] = num.num % 10;
		num.num /= 10;
	}

	for(uint8_t i = 0; i < 4; i++)
	{
		digit = DIGITS[digits[i]];
		if(num.pointPos == i + 1)
			digit &= DPOINT;
		showDigitOnSegment(digit, i + 1);
	}
}

void LEDInit()
{
	CONTROLDDR |= 	0b11111111;
	LEDDDR |= 		0b11111111;
}
