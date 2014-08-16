/*
 * Buzzer.cpp
 *
 *  Created on: 6 sie 2014
 *      Author: vka
 */

#include "Buzzer.h"

Buzzer::Buzzer() {

	handle = this;

	this->buzz.freq = 0;
	this->buzz.length = 0;
	this->buzz.timePlayed = 0;
	this->buzz.tick = 0;
	this->buzz.halfPeriod = 0;
	this->buzz.play = false;

	this->DDR = 0;
	this->PORT = 0;
	this->pin = 0;

	this->scale = 100;
}

void Buzzer::init()
{
	*this->DDR |= 1 << this->pin;
	*this->PORT &= ~(1 << this->pin);

	this->initTimer();
}

void Buzzer::setOutput(volatile uint8_t * DDRReg, volatile uint8_t * PORTReg, uint8_t pinNum)
{
	this->DDR = DDRReg;
	this->PORT = PORTReg;
	this->pin = pinNum;
}

void Buzzer::setBuzz(const uint16_t freq, const uint32_t length)
{
	this->buzz.freq = freq;
	this->buzz.length = length;
	this->buzz.timePlayed = 0;
	this->buzz.tick = 0;
	this->buzz.halfPeriod = F_CPU / (freq * 2);
	this->buzz.play = false;
}

void Buzzer::initTimer()
{
	TIMSK |= _BV(OCIE1A);
	TCCR1A = _BV(COM1A0) | _BV(COM1B0);

	OCR1A = F_CPU / (1000000 / this->scale);

	TCCR1B = _BV(WGM12) | _BV(CS10);
}

void Buzzer::handleInterrupt()
{
	if(this->buzz.timePlayed >= this->buzz.length)
		this->buzz.play = false;

	if(this->buzz.play)
	{
		//*this->PORT ^= ~(*this->PORT) & (1 << this->pin);

		this->buzz.timePlayed+= this->scale;
		this->buzz.tick+= this->scale;

//		if(this->buzz.tick * this->scale * 2 * this->buzz.freq > F_CPU)
//		{
//			*this->PORT = ~(*this->PORT) | (0xff & (~(1 << this->pin)));//todo
//			this->buzz.tick = 0;
//		}//if((this->buzz.timePlayed % (F_CPU / this->buzz.freq)) * this->buzz.freq > F_CPU)
//		if((this->buzz.timePlayed % (F_CPU / this->buzz.freq)) * 2 * this->buzz.freq > F_CPU)
//			*this->PORT |= 1 << this->pin;
//		else
//			*this->PORT &= ~(1 << this->pin);
		if(this->buzz.tick > this->buzz.halfPeriod)
		{
			*this->PORT = ~(*this->PORT);// | (0xff & (~(1 << this->pin)));
			this->buzz.tick = 0;
		}
		//else
			//*this->PORT &= ~(1 << this->pin);


	}
	else
		this->reset();
}

void Buzzer::play()
{
	this->buzz.play = true;
	sei();
}

void Buzzer::abort()
{
	cli();
	this->buzz.play = false;
}

void Buzzer::reset()
{
	this->abort();

	*this->PORT &= ~(1 << this->pin);

	this->buzz.timePlayed = 0;
	this->buzz.tick = 0;
	this->buzz.play = false;
}

const Buzzer::Buzz Buzzer::getBuzz()
{
	return this->buzz;
}

void handleInterrupt(Buzzer * b)
{
	b->handleInterrupt();
}

ISR(TIMER1_COMPA_vect)
{
	handleInterrupt(handle);
}
