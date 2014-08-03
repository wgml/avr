/*
 * SPI.cpp
 *
 *  Created on: 2 sie 2014
 *      Author: vka
 */

#include "SPI.h"

SPI::SPI() {
	// TODO Auto-generated constructor stub

	this->SPIenabled = 	true;
	this->clockPhase = 	true;
	this->clockPolarity = 	true;
	this->dataOrder = 	true;
	this->isMaster = 	true;

	this->DDR = this->PORT = 0;
	this->MISO = this->MOSI = this->SS = this->SCK = 0;
}

SPI::SPI(bool dataOrder, bool clockPolarity, bool clockPhase, bool isMaster, bool SPIenabled)
{
	this->SPIenabled = 	SPIenabled;
	this->clockPhase = 	clockPhase;
	this->clockPolarity = 	clockPolarity;
	this->dataOrder = 	dataOrder;
	this->isMaster = 	isMaster;

	this->DDR = this->PORT = 0;
	this->MISO = this->MOSI = this->SS = this->SCK = 0;
}

void SPI::setIOParams(volatile uint8_t * ddr, volatile uint8_t * port, uint8_t SS, uint8_t SCK, uint8_t MOSI, uint8_t MISO)
{
	this->DDR = 	ddr;
	this->PORT = 	port;
	this->SS = 	SS;
	this->SCK = 	SCK;
	this->MOSI = 	MOSI;
	this->MISO = 	MISO;
}

void SPI::init(void)
{
	SPCR = 0;
	SPCR 	|= this->SPIenabled << SPE
		| this->dataOrder << DORD
		| this->isMaster << MSTR
		| this->clockPolarity << CPOL
		| this->clockPhase << CPHA;

	*this->DDR |= _BV(this->SS) | _BV(this->SCK);
	if(this->isMaster)
		*this->DDR |= _BV(this->MOSI);
	else
		*this->DDR |= _BV(this->MISO);

	SPSR; //todo ?
	SPDR; //todo ?
}


void SPI::setClockPhase(bool phase)
{
	this->clockPhase = phase;
}

void SPI::setClockPolarity(bool polarity)
{
	this->clockPolarity = polarity;
}

void SPI::setDataOrder(bool order)
{
	this->dataOrder = order;
}

void SPI::setMaster(bool master)
{
	this->isMaster = master;
}

void SPI::setSPIEnabled(bool enabled)
{
	this->SPIenabled = enabled;
}

void SPI::sendByte(uint8_t byte)
{
	*this->PORT &= ~_BV(this->SS);
	SPDR = byte;

	while(!(SPSR & _BV(SPIF)));
	*this->PORT |= _BV(this->SS);

}

void SPI::sendWord(uint16_t word)
{
	*this->PORT &= ~_BV(this->SS);
	if(this->dataOrder)
		SPDR = word & 0xFF;
	else
		SPDR = (word >> 8) & 0xFF;

	while(!(SPSR & _BV(SPIF)));

	if(this->dataOrder)
		SPDR = (word >> 8) & 0xFF;
	else
		SPDR = word& 0xFF;

	while(!(SPSR & _BV(SPIF)));

	*this->PORT |= _BV(this->SS);
}
