/* MIT License
 * Copyright (c) 2017 Justin Decker
 * Copyright (c) 2022 Dirk O. Kaar <dok@dok-net.net>
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Datasheet: https://www.analog.com/en/products/ad5243.html
 * Resistance set is measured between B1 and W1 for channel 0, and B2 and W2 for channel 1
 * */

#include "ad5243.h"

bool AD5243::connected()
{
	_i2cPort.beginTransmission(_address);
	uint8_t retval = _i2cPort.endTransmission();

	if (retval)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool AD5243::setResistance(uint8_t channel, long resistance)
{
	uint8_t b[2];
	const uint8_t step = (255.0 * ((float)resistance / (float)_total_resistance));

	b[0] = (channel ? 0x80 : 0x00) | (!resistance ? 0x40 : 0x00);
	b[1] = step;
	_i2cPort.beginTransmission(_address);
	_i2cPort.write(b, 2);
	uint8_t retval = _i2cPort.endTransmission();

	if (retval)
	{
		return false;
	}
	else
	{
		if (!channel)
		{
			channel1Resistance = resistance;
		}
		else
		{
			channel2Resistance = resistance;
		}
		return true;
	}
}

uint8_t AD5243::readControlRegister()
{
	_i2cPort.requestFrom(_address, 1U);
	return _i2cPort.read();
}