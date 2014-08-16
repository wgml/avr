/*
 * main.cpp
 *
 *  Created on: 6 sie 2014
 *      Author: vka
 */

#include <util/delay.h>

#include "Buzzer.h"
#include "LCD/LCD.h"
#include <util/delay.h>

int main()
{
	LCD lcd;
	Buzzer b;
	Buzzer::Buzz buzz;

	lcd.setCursorVisibility(false, false);
	lcd.setFunction(false, true, true);
	lcd.init();



	b.setOutput(&DDRD, &PORTD, 7);
	b.setBuzz(0, 500000);
	b.init();

	b.play();

	lcd.clear();

	while(1)
	{
		buzz = b.getBuzz();
		lcd.goToPos(0, 0);
		lcd.sendText("Play: ");
		lcd.sendInt(buzz.play);
		lcd.sendText(" L: ");
		lcd.sendInt(buzz.length / 1000);
		lcd.sendText("ms");
		lcd.goToPos(1, 0);
		lcd.sendText("F: ");
		lcd.sendInt(buzz.freq);
		lcd.sendText(" T: ");
		lcd.sendInt(buzz.timePlayed / 1000);
		lcd.sendText("ms  ");

		if(!buzz.play)
		{
			_delay_ms(500);
			b.setBuzz((buzz.freq + 1000) % 20000, 500000);
			b.play();
		}
	}
}




//int main()
//{
//	DDRD |= _BV(7);
//	PORTD = 1 << 7;
//	uint32_t freq = 0;//Hz;
//	int8_t dir = 1;
//	int16_t multi = 1;
//	uint32_t iter = 0;
//	LCD lcd;
//	lcd.setCursorVisibility(false, false);
//	lcd.setFunction(false, true, true);
//	lcd.init();
//	lcd.sendText("Init...");
//	while(1)
//	{
//		if(iter * 20 >= freq)
//		{
//			if(freq >= 20000)
//				dir = -1;
//
//			else if(freq <= 1)
//				dir = 1;
//
//			if(freq == 10)
//			{
//				if(dir == 1)
//					multi = 10;
//				else
//					multi = 1;
//			}
//			else if(freq == 100)
//			{
//				if(dir == 1)
//					multi = 100;
//				else
//					multi = 10;
//			}
//			else if(freq == 1000)
//			{
//				if(dir == 1)
//					multi = 1000;
//				else
//					multi = 100;
//			}
//
//
//			freq += multi * dir;
//			iter = 0;
//			//lcd.clear();
//			lcd.sendText("\nCPU: ");
//			lcd.sendInt(F_CPU);
//			lcd.sendText("Hz\nFreq: ");
//			lcd.sendInt(freq);
//			lcd.sendText("Hz ");
//		}
//
//		PORTD = ~PORTD;
//		for(uint32_t i = 0; i < 1000000 / (2UL * freq); i++)
//			_delay_us(1);
//
//		iter++;
//		//PORTD = ~PORTD;
//		//_delay_us(100);
//	}
//}
