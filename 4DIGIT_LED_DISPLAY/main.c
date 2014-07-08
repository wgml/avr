/*
 * main.c
 *
 *  Created on: 8 lip 2014
 *      Author: vka
 */

#include "leddisp.h"

class Test
{
public:
	uint8_t val;
};


int main()
{
	LEDInit();
	struct Number num = {11, 3};
	while(1)
	{

		showNumberOnDisplay(num);
	}
}

