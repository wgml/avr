/*
 * SPI.h
 *
 *  Created on: 2 sie 2014
 *      Author: vka
 */

#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
class SPI {
public:
	SPI();
	SPI(bool dataOrder, bool clockPolarity, bool clockPhase, bool isMaster, bool SPIenabled);

	void 		init();

	void 		sendByte(uint8_t byte);
	uint8_t		receiveByte(void); 	//todo

	void 		sendWord(uint16_t word);
	uint16_t 	receiveWord(void);	//todo

	void 		setDataOrder(bool order);
	void 		setClockPolarity(bool polarity);
	void 		setClockPhase(bool phase);
	void 		setMaster(bool master);
	void 		setSPIEnabled(bool enabled);

	void 		setIOParams(volatile uint8_t * ddr, volatile uint8_t * port, uint8_t SS, uint8_t SCK, uint8_t MOSI, uint8_t MISO);

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
