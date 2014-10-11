/*
 * SDCard.cpp
 *
 *  Created on: 11 paź 2014
 *      Author: vka
 */

#include "SDCard.h"

SDCard::SDCard() {
	// TODO Auto-generated constructor stub
	this->port = 0;
	this->ddr = 0;
	this->cs = 0;
}

void SDCard::setIO(volatile uint8_t * port, volatile uint8_t * ddr, uint8_t cs)
{
	this->port = port;
	this->ddr = ddr;
	this->cs = cs;
}
