/*
 * leddisp.c
 *
 *  Created on: 8 lip 2014
 *      Author: vka
 */

#include "leddisp.h"
#include <util/delay.h>
//#include "timer.h"

const uint8_t DIGITS[10] = {	DIG0, 	DIG1, 	DIG2, 	DIG3,
								DIG4,	DIG5, 	DIG6, 	DIG7,
								DIG8, 	DIG9	};

void showCharOnSegment(uint8_t digit, uint8_t seg)
{
	/*
	 * assumes it is given valid data
	 * and sets output value.
	 */

	CONTROLPORT = ~(1 << (seg - 1));
	LEDPORT = digit;
	_delay_us(500); //todo

}

void showNumberOnDisplay(Number num)
{
	/*
	 * manages whole display.
	 * It uses showCharOnSegment function
	 * to set values for each segment.
	 * //todo checks if given value is in
	 * proper range(-999 - +9999, also point
	 * in 1-4 range.
	 * //todo option to skip leading 0s.
	 */

	if((num.minus == 1 && num.num > 999)
		|| (num.minus == 0 && num.num > 9999)
		|| (num.pointPos > 4)
		|| (num.pointPos == 1 && num.minus == 1))
		LEDsetError(0);
	else
	{
		uint8_t values[4], value;

		for(uint8_t i = 0; i < 4; i++)
		{
			values[3 - i] = DIGITS[num.num % 10];
			num.num /= 10;

			if(num.num == 0)
			{
				if(num.skipZeros == 0)
				{
					for(uint8_t j = i + 1; j < 4; j++)
					{
						values[3 - j] = DIGITS[0];
					}

					if(num.minus == 1)
						values[0] = DMINUS;
				}
				else
				{
					for(uint8_t j = i + 1; j < 4; j++)
					{
						values[3 - j] = DOFF;
					}

					if(num.minus == 1)
						values[2 - i] = DMINUS;
				}

				break;
			}
		}

		for(uint8_t i = 0; i < 4; i++)
		{
			value = values[i];
			if(num.pointPos == i + 1)
				value &= DPOINT;
			showCharOnSegment(value, i + 1);
		}
	}
}

void LEDInit()
{
	/*
	 * responsible for setting proper
	 * register values. For now, it uses
	 * whole two ports.
	 */
	CONTROLDDR |= 	0b11001111;
	LEDDDR |= 		0b11111111;
}

void LEDTest()
{
	/*
	 * sets all LEDs to shine
	 */
	CONTROLPORT = 0b0000;
	LEDPORT = 0b00000000;
}

void LEDReset()
{
	/*
	 * sets all LEDs off-state.
	 */
	CONTROLPORT = 0b1111;
		LEDPORT = 0b11111111;
}

void LEDsetError(uint8_t err)
{
	/*
	 * sets error message on led display.
	 * Error codes:
	 * ERR0:	number out of range
	 * ERR9:	error code out of range
	 */

	uint8_t errDigit;

	if(err > 9)
		errDigit = DIGITS[9];
	else
		errDigit = DIGITS[err];

	showCharOnSegment(LETE, 1);
	showCharOnSegment(LETR, 2);
	showCharOnSegment(LETR & DPOINT, 3);
	showCharOnSegment(errDigit, 4);
}
