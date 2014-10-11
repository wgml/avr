/*
 * SDCard.h
 *
 *  Created on: 11 paź 2014
 *      Author: vka
 */

#ifndef SDCARD_H_
#define SDCARD_H_

#include "SPI/SPI.h"

class SDCard {
public:
	SDCard();
	void setIO(volatile uint8_t *, volatile uint8_t *, uint8_t);
private:
	SPI spi;
	volatile uint8_t * 	ddr;
	volatile uint8_t * 	port;
	uint8_t			cs;

};

#endif /* SDCARD_H_ */
