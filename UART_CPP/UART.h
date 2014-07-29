/*
 * UART.h
 *
 *  Created on: 27 lip 2014
 *      Author: vka
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

class UART {
public:
	UART();

	void 	init();

	uint8_t receive();
	void 	send(uint8_t);
private:
	void 	init_9600();

};

#endif /* UART_H_ */
