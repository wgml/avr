/*
 * number.h
 *
 *  Created on: 10 lip 2014
 *      Author: vka
 */

#ifndef NUMBER_H_
#define NUMBER_H_

typedef struct Number
{
	uint16_t num;
	uint8_t pointPos;
	uint8_t minus;
	uint8_t skipZeros;
} Number;

#endif /* NUMBER_H_ */
