/*
 * SD.cpp
 *
 *  Created on: 14 sie 2014
 *      Author: vka
 */

#include "SD.h"

SD::SD()
{
	this->buffer = 0;
	this->uart = 0;
	this->debugMode = true;

	//UART communication init
	if(this->debugMode && this->uart)
		this->uart->sendText((int8_t*)"UART init successful.\n");

	//SPI communication init
	this->spi.setIOParams(&DDRB, &PORTB, 4, 7, 5, 6);
	this->spi.setDataOrder(false);
	this->spi.init();

	if(this->debugMode && this->uart)
		this->uart->sendText((int8_t *)"SPI init successful.\n");

	//buffer init
	this->buffer = (uint8_t *) malloc(BUFFER_LENGTH);

	if(!this->buffer)
		this->~SD();

	if(this->debugMode && this->uart)
		this->uart->sendText((int8_t *)"Buffer init successful.\n");
}

void SD::init()
{
	this->spi.CSDisable();
	for(int i = 0; i < 10; i++)
	{
		if(this->debugMode && this->uart)
		{
			this->uart->sendText((int8_t *)"Sending byte ");
			this->uart->sendHex(0xFF);
		}

		this->spi.sendByte(0xFF, true); //send 80 clocks to sd card to give it time to init

		if(this->debugMode && this->uart)
			this->uart->sendText((int8_t *)"... Byte sent.\n");
	}

	if(this->debugMode && this->uart)
		this->uart->sendText((int8_t *)"SD given 80 ticks successful.\n");


	//[0x40 0x00000000 0x95, r8] until get 1
	uint8_t val = 0;
	uint8_t i;
	uint8_t tries = 10;
	for(i = 0; i < tries; i++)
	{
		if(this->debugMode && this->uart)
			this->uart->sendText((int8_t *)"Sending 0x40 0x00000000 0x95, r8.\n");

		/*val = */this->sendCmd(0x40, 0x00000000, 0x95, 8);

		if(this->debugMode && this->uart)
			this->uart->sendText((int8_t *)"Command sent.\n");

		if(val == 1)
		{
			if(this->debugMode && this->uart)
				this->uart->sendText((int8_t *) "SD init successful.\n");
			return;
		}
		else
			_delay_ms(100);
	}

	if(i == tries)
	{
		//init failed
		if(this->debugMode && this->uart)
			this->uart->sendText((int8_t *) "SD init failed.\n");
	}
}

void SD::sendCmd(uint8_t cmd, uint32_t args, uint8_t crc, uint8_t read)
{

	//this->spi.CSEnable();

	this->spi.sendByte(cmd);
	this->spi.sendByte(args >> 24);
	this->spi.sendByte(args >> 16);
	this->spi.sendByte(args >> 8);
	this->spi.sendByte(args);
	this->spi.sendByte(crc);


	for(uint8_t i = 0; i < read; i++)
		this->buffer[i] = this->spi.sendByte(0xFF); //send dummy to receive data

	//this->spi.CSDisable();

	if(this->debugMode && this->uart)
	{
		this->uart->sendText((int8_t *)"Sent command to sd. Response: ");
		for(uint8_t i = 0; i < read; i++)
		{
			this->uart->sendHex(this->buffer[i]);
			this->uart->sendText((int8_t *) " ");
		}
		this->uart->sendText((int8_t *) "\n");
	}
}

void SD::setUART(UART * uart)
{
	this->uart = uart;
}
