/*
 * leddisplay.c
 *
 *  Created on: 13 lip 2014
 *      Author: Wojtek Gumuła
 */

#include "leddisplay.h"
#include <util/delay.h>

void LEDInit()
{
	/*
	 * call this function on start
	 */

	CONTROLDDR |= 	0b1111;
	LEDDDR |= 	0b11111111;

}

void LEDTest()
{
	/*
	 * set all segments to work
	 */

	_segments[0] =	~DOFF;
	_segments[1] =	~DOFF;
	_segments[2] =	~DOFF;
	_segments[3] =	~DOFF;
}

void LEDshowOnDisplay()
{
	if(display.changed == 1)
	{
		_LEDupdateSegments();
		display.changed = 0;
	}

	for(uint8_t seg = 1; seg <= 4; seg++)
	{

		CONTROLPORT = 	~(1 << (seg - 1));
		LEDPORT = 	_segments[seg - 1];

		_delay_us(100); //todo what do to?
		LEDPORT =	DOFF;
	}
}

static void _LEDsetValueOnSegment(uint8_t value, uint8_t seg)
{
	/*
	 * set value arg1 on segment arg2
	 */
	if(seg > 0 && seg <= 4)
		_segments[seg - 1] = value;
}

static void _LEDsetErrorMessage(uint8_t err)
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

	_LEDsetValueOnSegment(LETE, 1);
	_LEDsetValueOnSegment(LETR, 2);
	_LEDsetValueOnSegment(LETR & DPOINT, 3);
	_LEDsetValueOnSegment(errDigit, 4);
}

static void _LEDupdateSegments()
{
	/*
	 * converts display variable into struct segments variable
	 * should be called every time a display structure changes
	 */
	if((display.isNegative == 1 && display.number > 999)
			|| (display.number > 9999))
	{
		_LEDsetErrorMessage(0);
	}
		else
		{
			uint8_t values[4];

			for(uint8_t i = 0; i < 4; i++)
			{
				values[3 - i] = DIGITS[display.number % 10];
				display.number /= 10;

				if(display.number == 0)
				{
					if(display.skipZeros == 0)
					{
						for(uint8_t j = i + 1; j < 4; j++)
						{
							values[3 - j] = DIGITS[0];
						}

						if(display.isNegative == 1)
							values[0] = DMINUS;
					}
					else
					{
						for(uint8_t j = i + 1; j < 4; j++)
						{
							if(!((display.pointPos >> j) == 1) && (display.forceFractZero == 1))
								values[3 - j] = DOFF;
						}

						if(display.isNegative == 1)
							values[2 - i] = DMINUS;
					}

					break;
				}
			}

			for(uint8_t i = 0; i < 4; i++)
			{
				if((display.blinkPos & (1 <<(3 - i))) != 0)
					_segments[i] = DOFF;
				else
				{
					_segments[i] = values[i];

					if((display.pointPos & (1 << (3 - i))) != 0)
						_segments[i] &= DPOINT;
				}
			}
		}
}
