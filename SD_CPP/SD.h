/*
 * SD.h
 *
 *  Created on: 14 sie 2014
 *      Author: vka
 */

#ifndef SD_H_
#define SD_H_

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

#include "SPI/SPI.h"
#include "UART/UART.h"

#define BUFFER_LENGTH 32

class SD {
public:
	SD();

	void init();

	void seek();
	void tell();
	void read();
	void write();

	void setUART(UART * uart);
private:

	SPI spi;
	UART * uart;
	uint8_t * buffer;
	bool debugMode;

	void sendCmd(uint8_t cmd, uint32_t args, uint8_t crc, uint8_t read);

};

#endif /* SD_H_ */
