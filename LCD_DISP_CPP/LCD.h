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
//#include <stdlib.h> //malloc

class LCD {
public:
	LCD();
	~LCD();

	void init(void);
	void stop(void);

	void goToPos(uint8_t line, uint8_t pos);
	void sendText(const char[]/*, uint8_t seg = 0*/, uint8_t msDelay = 0);

	void clear(void);

	void setCursorVisibility(bool visible, bool blinking);
	void setFunction(bool eightBitPatch, bool twoLines, bool font5x10);

	//void setNumSegments(uint8_t num);
	//uint8_t getNumSegments(void);

private:

	void sendChar(uint8_t c); //todo

	//bool isSegmentChanged(uint8_t num); //todo

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

	/*struct Segment
	{
		uint8_t 	width;
		uint8_t 	height;

		char * 		container;

		bool 		changed;
	} * segments;

	uint8_t 		numSegments; //choose between 1, 2 or 4*/

};

#endif /* LCD_H_ */
