/*
 * LCD.cpp
 *
 *  Created on: 24 lip 2014
 *      Author: vka
 */

#include "LCD.h"
#include "hd44780/hd44780.c"

LCD::LCD() {
	//defaults
	this->cursor.x = 0;
	this->cursor.y = 0;
	this->cursor.visible = true;
	this->cursor.blinking = true;
	this->twoLines = true;
	this->font5x10 = false;
	this->eightBitPatch = false;
}

LCD::~LCD() {
	// TODO Auto-generated destructor stub
}

void LCD::init()
{
	//todo
	hd44780_init();

	hd44780_outcmd(HD44780_CLR); //clear screen
	hd44780_wait_ready(true);

	hd44780_outcmd(HD44780_ENTMODE(1, 0)); //set address auto-inc, non-auto display shift
	hd44780_wait_ready(false);

	hd44780_outcmd(HD44780_DISPCTL(1, this->cursor.visible, this->cursor.blinking)); //disp on, curs on, curs blink on
	hd44780_wait_ready(false);

	hd44780_outcmd(HD44780_FNSET(this->eightBitPatch, this->twoLines, this->font5x10));
	hd44780_wait_ready(false);

	this->cursor.x = 0;
	this->cursor.y = 0;
}

void LCD::stop()
{
	//todo
	hd44780_powerdown();
}

void LCD::sendChar(uint8_t c)
{
	/*
	 * every other \n char clears LCD.
	 */
	//todo

	if(c == '\n')
	{
		if(this->cursor.y == 1)
		{
			//clear screen and go back to (0, 0)
			//this->clear();
			this->goToPos(0, 0);
		}
		else
			this->goToPos(1, 0);
	}
	else
	{
		hd44780_outdata(c);
		this->cursor.iter();
		hd44780_wait_ready(false);
	}

}

void LCD::sendText(const char * txt, uint8_t delay)
{
	while(*txt)
	{
		this->sendChar(*txt++);

		if(delay != 0)
		{
			for(uint8_t i = 0; i < delay; i++)
				_delay_ms(1);
		}
	}
}

void LCD::sendInt(int32_t num, uint8_t msDelay)
{
	uint8_t len = 1;
	int32_t temp;

	if(num < 0)
	{
		temp = -num;
		len++;
	}
	else
		temp = num;

	while((temp /= 10) != 0)
		len++;

	char buffer[len + 1];

	if(num < 0)
		temp = -num;
	else
		temp = num;

	for(uint8_t i = len; i > 0; i--, temp /= 10)
		buffer[i - 1] = temp % 10 + 48;

	if(num < 0)
		buffer[0] = '-';

	buffer[len] = 0;

	this->sendText(buffer,  msDelay);
}

void LCD::sendDigit(uint8_t digit)
{
	this->sendChar(digit + 48);
}

void LCD::goToPos(uint8_t line, uint8_t pos)
{
	if(line < 2 && pos < 40 && !(this->cursor.x == pos && this->cursor.y == line))
	{
		hd44780_outcmd(0x80 | (pos + (0x40 * line)));

		this->cursor.x = pos;
		this->cursor.y = line;

		hd44780_wait_ready(false);
	}
}

void LCD::clear()
{
	hd44780_outcmd(HD44780_CLR);
	hd44780_wait_ready(true);

	this->goToPos(0, 0);
}

void LCD::setCursorVisibility(bool visible, bool blinking)
{
	this->cursor.visible = visible;
	this->cursor.blinking = blinking;
}

void LCD::setFunction(bool eightBitPatch, bool twoLines, bool font5x10)
{
	this->eightBitPatch = eightBitPatch;
	this->twoLines = twoLines;
	this->font5x10 = font5x10;
}

void LCD::defineChar(uint8_t no, uint8_t * c)
{
	if(no > 7 || (this->font5x10 && no > 3))
		return;

	hd44780_outcmd(HD44780_CGADDR(no * 8));
	hd44780_wait_ready(true);

	for(uint8_t i = 0; i < 8; i++)
	{
		hd44780_outdata(c[i]);
		hd44780_wait_ready(true);
	}

	hd44780_outcmd(HD44780_DDADDR(0));
	hd44780_wait_ready(true);
}

void LCD::sendSpecialChar(uint8_t no)
{
	if(no > 7 || (this->font5x10 && no > 3))
		return;

	hd44780_outcmd(HD44780_CGADDR(no * 8));
	hd44780_wait_ready(true);

	this->sendChar(no);

	hd44780_outcmd(HD44780_DDADDR(0));
	hd44780_wait_ready(true);
}
