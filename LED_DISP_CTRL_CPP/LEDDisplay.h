/*
 * LEDDisplay.h
 *
 *  Created on: 23 lip 2014
 *      Author: vka
 */

#ifndef LEDDISPLAY_H_
#define LEDDISPLAY_H_

#include <avr/io.h>
#include <util/delay.h>

class LEDDisplay {
public:
	LEDDisplay();
	LEDDisplay(volatile uint8_t *, volatile uint8_t *, volatile uint8_t *, volatile uint8_t *, uint8_t, bool);
	~LEDDisplay();

	void setDisplayPort(volatile uint8_t *, volatile uint8_t *);
	void setControlPort(volatile uint8_t *, volatile uint8_t *);
	void setDisplayMode(bool isCommonAnode = true);
	void setBrightness(uint8_t);

	void init();
	void test();

	void update();

	volatile struct Display
	{
		/*
		 * contains values to show on each segment
		 * segments are labeled as follows
		 * -----------------
		 * | 1 | 2 | 3 | 4 |
		 * -----------------
		 * Each variable should be set with 8-bit number
		 * containing information about lightening each seg.
		 * For easy use, standard characters are defined.
		 * Defining more chars is possible and simple.
		 * There is no need to define then in defines.h file,
		 * as you can simply use hex or binary number in structure.
		 *
		 */

		uint16_t 	number;
		uint8_t 	pointPos; 	//0b0110, 1 if show point on seg i.
		uint8_t 	blinkPos; 	//as before
		uint8_t		isNegative;	//set 1 if to show '-'
		uint8_t 	skipZeros;	//set 1 if to skip leading zeros.
		uint8_t 	changed;	//flag you need to set if you change struct.
		uint8_t 	forceFractZero;	//set 1 if desired format is 0.12 instead of .12

	} display;



private:

	void updateSegments();
	void LEDsetErrorMessage(uint8_t);

	bool			isCommonAnode;
	volatile uint8_t *	controlDDR;
	volatile uint8_t *	controlPORT;
	volatile uint8_t *	displayDDR;
	volatile uint8_t *	displayPORT;
	uint8_t 		brightness;
	volatile uint8_t	segments[4];
};

#define DIG0		0b11000000
#define DIG1		0b11111001
#define DIG2		0b10100100
#define DIG3		0b10110000
#define DIG4		0b10011001
#define DIG5		0b10010010
#define DIG6		0b10000010
#define DIG7		0b11111000
#define DIG8		0b10000000
#define DIG9		0b10010000
#define DMINUS		0b10111111
#define DPOINT		0b01111111
#define DOFF 		0b11111111
#define LETE		0b10000110
#define LETR		0b10101111

const uint8_t digits[10] = {DIG0, DIG1, DIG2, DIG3, DIG4, DIG5,DIG6, DIG7, DIG8, DIG9};


#endif /* LEDDISPLAY_H_ */
