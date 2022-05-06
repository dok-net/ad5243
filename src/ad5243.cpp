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
 * Resistance set is measured between B1 and W1 for channel 0, and B2 and W2
 * for channel 1
 */

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

long AD5243::computedResistance(const uint8_t data)
{
	return (data * _nominal_resistance + 128) / 256 + 2 * _wiper_resistance;
}

bool AD5243::setData(uint8_t channel, uint8_t data)
{
	uint8_t b[2];
	b[0] = (channel ? 0x80 : 0x00) | (data ? 0x00 : 0x40);
	b[1] = data;
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
			channel1Data = data;
		}
		else
		{
			channel2Data = data;
		}
		return true;
	}
}

bool AD5243::setResistance(uint8_t channel, const long resistance)
{
	const uint8_t data = resistance - 2 * _wiper_resistance > 0 ?
		((resistance - 2 * _wiper_resistance) * 256 + _nominal_resistance / 2)
			/ _nominal_resistance :
		0;
	return setData(channel, data);
}

uint8_t AD5243::readControlRegister()
{
	_i2cPort.requestFrom(_address, 1U);
	return _i2cPort.read();
}
