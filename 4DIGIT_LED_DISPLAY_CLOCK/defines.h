/*
 * defines.h
 *
 *  Created on: 8 lip 2014
 *      Author: vka
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#include <avr/io.h>
#include "number.h"
/*
 * program uses whole 8-pin port for
 * digit displaying, and also pins
 * 0-5 from other port for managing
 * pin 4 is CLOCK_ENABLE
 * and pin 5 is CLOCK_RESET
 */

#define LEDDDR 		DDRA
#define LEDPORT 	PORTA
#define CONTROLDDR 	DDRD
#define CONTROLPORT	PORTD
#define CONTROLPIN	PIND

//do not change anything behind this point

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

#endif /* DEFINES_H_ */
