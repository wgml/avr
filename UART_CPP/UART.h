/*
 * UART.h
 *
 *  Created on: 27 lip 2014
 *      Author: vka
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include <stdlib.h>

class UART {
public:
	UART();
	~UART();

	void 		init(void);

	uint8_t		receiveChar(void);
	void 		sendChar(uint8_t);

	uint8_t *	receiveText(uint8_t length = 20, uint8_t terminate = '\0'); //todo
	void 		sendText(const uint8_t *); //todo

	void 		initBuffer(uint8_t size = 20);
	uint8_t 	getBufferSize(void);
	uint8_t *	getBufferPointer(void);

private:
	void 		init_9600();

	uint8_t *	buffer;
	uint8_t		bufferSize;
};

#endif /* UART_H_ */
