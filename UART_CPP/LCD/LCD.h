/*
 * LCD.h
 *
 *  Created on: 24 lip 2014
 *      Author: vka
 */
 //segments connected funcions will be written in another proj.
#ifndef LCD_H_
#define LCD_H_

#include "hd44780/hd44780.h" //todo own implementation?
#include <util/delay.h>

class LCD {
public:
	LCD();
	~LCD();

	void init(void);
	void stop(void);

	void goToPos(uint8_t line, uint8_t pos);
	void sendText(const char[]/*, uint8_t seg = 0*/, uint8_t msDelay = 0);
	void sendText(uint8_t c);
	void sendChar(uint8_t c);

	void clear(void);

	void setCursorVisibility(bool visible, bool blinking);
	void setFunction(bool eightBitPatch, bool twoLines, bool font5x10);

private:
	struct Cursor
	{
	 	 uint8_t 	x, y;
	 	 bool 		visible;
	 	 bool		blinking;
	 	 void iter()
	 	 {
	 		 if(this->x <39)
	 			 this->x++;
	 		 else
	 		 {
	 			 this->x = 0;
	 			 this->y = (this->y + 1) % 2;
	 		 }
	 	 }
	} cursor;

	bool		eightBitPatch;
	bool		font5x10;
	bool		twoLines;//todo wrap params inside struct?

};

#endif /* LCD_H_ */
