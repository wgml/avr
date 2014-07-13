/*
 * defines.h
 *
 *  Created on: 13 lip 2014
 *      Author: Wojtek Gumuła
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#include <avr/io.h>
/*
 * Port definitions below, driver uses  whole one port
 * for segments control purpose and half of other port
 * for controlling active segment.
 */
#define LEDDDR 		DDRA		//ie. DDRA
#define LEDPORT 	PORTA		//ie. PORTA
#define CONTROLDDR 	DDRD		//ie. DDRB
#define CONTROLPORT	PORTD		//ie. PORTB
#define CONTROLPIN	PIND		//ie. PINB

#define COMMONANODE	1		//set 1 if LEDs have common anode, 0 otherwise

/*
 * chars definition follows,
 * you can add your own below.
 */

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
#define LETR		0b10001000

struct Display
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

	unsigned int 	number;
	unsigned char 	pointPos; 	//0b0110, 1 if show point on seg i.
	unsigned char 	blinkPos; 	//as before
	unsigned char 	isNegative;	//set 1 if to show '-'
	unsigned char 	skipZeros;	//set 1 if to skip leading zeros.
	unsigned char 	changed;	//flag you need to set if you change struct.
	unsigned char 	forceFractZero;	//set 1 if desired format is 0.12 instead of .12

};

#endif /* DEFINES_H_ */
