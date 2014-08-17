/*
 * LM35.h
 *
 *  Created on: 17 sie 2014
 *      Author: vka
 */

#ifndef LM35_H_
#define LM35_H_

#include "ADCChannel/ADCChannel.h"
#include <util/atomic.h>

class LM35: public ADCChannel {

public:
	LM35();
	uint32_t getValue();
};

static LM35 * handle;

#endif /* LM35_H_ */
