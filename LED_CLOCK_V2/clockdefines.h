/*
 * clockdefines.h
 *
 *  Created on: 14 lip 2014
 *      Author: vka
 */

#ifndef CLOCKDEFINES_H_
#define CLOCKDEFINES_H_

struct Time
{
	uint8_t 	hour;
	uint8_t 	minute;
	uint8_t 	second;
	uint8_t 	ms; 		//in hundreds
	uint8_t 	changed; 	//set 1 if display will need updating
};

enum State {CLOCK, SET_HOUR, SET_MINUTE};

#endif /* CLOCKDEFINES_H_ */
