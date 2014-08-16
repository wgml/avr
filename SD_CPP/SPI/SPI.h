/*
 * SPI.h
 *
 *  Created on: 2 sie 2014
 *      Author: vka
 */

/*
 * It is simple SPI interface written in C++.
 * Consider it not full product, which you can
 * modify to fit your purpose. SPI class doesn't
 * use interrupts, feel free to modify it.
 * Usage:
 * SPI comm(config values).
 * or
 * SPI comm;
 * comm.setDataOrder etc.
 * next
 * comm.setIO...
 * and next
 * comm.init().
 * Now you can use it.
 * Remember to call init() method every time you
 * change params.
 */


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

class SPI {
public:
	SPI();
	SPI(bool dataOrder, bool clockPolarity, bool clockPhase, bool isMaster, bool SPIenabled);

	void 		init();

	uint8_t 	sendByte(uint8_t byte, bool dummy = false);

	uint16_t 	sendWord(uint16_t word);

	void 		setDataOrder(bool order);
	void 		setClockPolarity(bool polarity);
	void 		setClockPhase(bool phase);
	void 		setMaster(bool master);
	void 		setSPIEnabled(bool enabled);

	void 		setIOParams(volatile uint8_t * ddr, volatile uint8_t * port, uint8_t SS, uint8_t SCK, uint8_t MOSI, uint8_t MISO);

	void		CSDisable();
	void		CSEnable();
private:
	bool	 	dataOrder;
	bool 		clockPolarity;
	bool 		clockPhase;
	bool 		isMaster;
	bool 		SPIenabled;

	volatile uint8_t * PORT;
	volatile uint8_t * DDR;
	uint8_t 	SS;
	uint8_t 	SCK;
	uint8_t 	MOSI;
	uint8_t 	MISO;
};

#endif /* SPI_H_ */
