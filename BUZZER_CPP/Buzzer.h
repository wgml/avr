/*
 * Buzzer.h
 *
 *  Created on: 6 sie 2014
 *      Author: vka
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include <avr/io.h>
#include <avr/interrupt.h>



class Buzzer {

	friend void handleInterrupt(Buzzer * b);
public:
	Buzzer();

	void 			init();

	void 			setOutput(volatile uint8_t * DDRReg, volatile uint8_t * PORTReg, const uint8_t pinNum);

	void 			setBuzz(const uint16_t freq, const uint32_t length);

	void			play();
	void			abort();
	void			reset();

	struct Buzz
	{
		uint16_t 	freq;
		uint32_t	length; //in microsecs
		uint16_t	tick;
		uint32_t	halfPeriod;
		bool		play;
		uint32_t 	timePlayed;
	};

	const Buzz 		getBuzz();
private:

	void			initTimer();
	void			handleInterrupt();

	volatile uint8_t * 	PORT;
	volatile uint8_t * 	DDR;
	uint8_t			pin;

	uint32_t		scale;

	struct Buzz 		buzz;
};

static Buzzer * handle;

void handleInterrupt(Buzzer * b);

#endif /* BUZZER_H_ */
