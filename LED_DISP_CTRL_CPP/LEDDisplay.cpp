/*
 * LEDDisplay.cpp
 *
 *  Created on: 23 lip 2014
 *      Author: vka
 */

#include "LEDDisplay.h"

LEDDisplay::LEDDisplay()
	: isCommonAnode(true), controlDDR(0), controlPORT(0), displayDDR(0), displayPORT(0), brightness(50)
{
	this->display.number = 0;
	this->display.blinkPos = 0;
	this->display.changed = true;
	this->display.forceFractZero = false;
	this->display.isNegative = false;
	this->display.pointPos = 0;
	this->display.skipZeros = false;
}

LEDDisplay::LEDDisplay(volatile uint8_t * ctrlDDR, volatile uint8_t * ctrlPORT, volatile uint8_t * dispDDR, volatile uint8_t * dispPORT, uint8_t brightness, bool comAnode)
	: isCommonAnode(comAnode), controlDDR(ctrlDDR), controlPORT(ctrlPORT), displayDDR(dispDDR), displayPORT(dispPORT), brightness(brightness)
{
	this->display.number = 0;
	this->display.blinkPos = 0;
	this->display.changed = true;
	this->display.forceFractZero = false;
	this->display.isNegative = false;
	this->display.pointPos = 0;
	this->display.skipZeros = false;

}

LEDDisplay::~LEDDisplay()
{
}

void LEDDisplay::init()
{
	/*
	 * sets proper port values on init.
	 * You need to call this function if you've used default constructor.
	 * You need to call setDisplayPort and setControlPort functions first!
	 */

	*(this->controlDDR) |= 	0b00001111;
	*(this->controlPORT) &=	0b11110000;
	*(this->displayDDR) |= 	0b11111111;

	for(uint8_t i = 0; i < 4; i++)
		this->segments[i] = DOFF;
}

void LEDDisplay::test()
{
	/*
	 * sets all leds to high potential
	 */

	for(uint8_t i = 0; i < 4; i++)
		this->segments[i] = (uint8_t) ~DOFF;
	this->brightness = 100;
}

void LEDDisplay::setDisplayPort(volatile uint8_t * ddr, volatile uint8_t * port)
{
	/*
	 * input are adresses to ddr and port registers of desired port.
	 * Remember to call init() function afterwards.
	 */
	this->displayDDR = ddr;
	this->displayPORT = port;
}

void LEDDisplay::setControlPort(volatile uint8_t * ddr, volatile uint8_t * port)
{
	/*
	 * input are adresses to ddr and port registers of desired port.
	 * Remember to call init() function afterwards.
	 */

	this->controlDDR = ddr;
	this->controlPORT = port;
}

void LEDDisplay::setDisplayMode(bool isCommonAnode)
{
	/*
	 * set true if LED is of common anode type, false otherwise.
	 */

	this->isCommonAnode = isCommonAnode;
}

void LEDDisplay::setBrightness(uint8_t brightness)
{
	/*
	 * brightness shall be number between 0 and 100
	 */
	if(brightness <= 100)
		this->brightness = brightness;
}

void LEDDisplay::update()
{
	/*
	 * main function you should call every time you
	 * want to set anything on screen.
	 * (LED display "works" just while this function is execute.
	 * See main.c for example.
	 */

	if(this->display.changed)
	{
		this->updateSegments();
		this->display.changed = false;
	}

	for(uint8_t seg = 0; seg < 4; seg++)
	{

		*(this->controlPORT) = 	~(1 << (seg));
		*(this->displayPORT) = 	this->segments[seg];

		for(uint8_t i = 0; i < this->brightness; i++)
			_delay_us(0.5);

		*(this->displayPORT) =	DOFF;

		for(uint8_t i = this->brightness; i < 100; i++)
			_delay_us(0.5);
	}
}

void LEDDisplay::updateSegments()
{
	/*
	 * internal function responsible for updating segments if changed.
	 */

	if((this->display.isNegative && this->display.number > 999)
			|| (this->display.number > 9999))
	{
		this->LEDsetErrorMessage(0);
	}
	else
	{
		uint8_t values[4];
		uint16_t dispVal = this->display.number;

		for(uint8_t i = 0; i < 4; i++)
		{
			values[3 - i] = digits[dispVal % 10];
			dispVal /= 10;

			if(dispVal == 0)
			{
				if(!this->display.skipZeros)
				{
					for(uint8_t j = i + 1; j < 4; j++)
					{
						values[3 - j] = digits[0];
					}

					if(this->display.isNegative)
						values[0] = DMINUS;
				}
				else
				{
					for(uint8_t j = i + 1; j < 4; j++)
					{
						if(!((this->display.pointPos >> j) == 1) && (this->display.forceFractZero))
							values[3 - j] = DOFF;
					}

					if(this->display.isNegative)
						values[2 - i] = DMINUS;
				}

				break;
			}
		}

		for(uint8_t i = 0; i < 4; i++)
		{
			if((this->display.blinkPos & (1 <<(3 - i))) != 0)
				this->segments[i] = DOFF;
			else
			{
				this->segments[i] = values[i];

				if((this->display.pointPos & (1 << (3 - i))) != 0)
					this->segments[i] &= DPOINT;
			}
		}
	}
}

void LEDDisplay::LEDsetErrorMessage(uint8_t error)
{
	/*
	 * sets error message on led display.
	 * Error codes:
	 * ERR0:	number out of range
	 * ERR9:	error code out of range
	 */

	uint8_t errDigit;

	if(error > 9)
		errDigit = digits[9];
	else
		errDigit = digits[error];

	this->segments[0] = LETE;
	this->segments[1] = LETR;
	this->segments[2] = LETR & DPOINT;
	this->segments[3] = errDigit;
}
