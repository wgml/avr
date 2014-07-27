/*
 * LCD.cpp
 *
 *  Created on: 24 lip 2014
 *      Author: vka
 */

#include "LCD.h"

LCD::LCD() {
	//defaults
	this->cursor.x = 0;
	this->cursor.y = 0;
	this->cursor.visible = true;
	this->cursor.blinking = true;
	this->twoLines = true;
	this->font5x10 = true;
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
			this->clear();
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
