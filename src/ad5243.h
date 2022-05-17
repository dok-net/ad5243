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
 */

#ifndef __ad5243_h
#define __ad5243_h

#include <Wire.h>

#define AD5243_I2C_ADDRESS 0x2c

class AD5243
{
private:
	uint8_t _address;
	TwoWire& _i2cPort;
	// according to datasheet, Rwiper is typical 160 ohm, max. 200 ohm
	const long _wiper_resistance;
	const long _nominal_resistance;
	uint8_t channel1Data = 0x80;
	uint8_t channel2Data = 0x80;

public:
	AD5243(long nominal_resistance, TwoWire& i2cPort = Wire) : _nominal_resistance(nominal_resistance), _wiper_resistance(160), _i2cPort(i2cPort)
	{
	}

	AD5243(long nominal_resistance, long wiper_resistance, TwoWire& i2cPort = Wire) : _nominal_resistance(nominal_resistance), _wiper_resistance(wiper_resistance), _i2cPort(i2cPort)
	{
	}

	bool begin(uint8_t address = AD5243_I2C_ADDRESS)
	{
		_address = address;
		return connected();
	}

	bool connected();

	uint8_t getChannel1Data()
	{
		return channel1Data;
	}

	uint8_t getChannel2Data()
	{
		return channel2Data;
	}

	long getChannel1Resistance()
	{
		return computedResistance(channel1Data);
	}

	long getChannel2Resistance()
	{
		return computedResistance(channel2Data);
	}

	long computedResistance(const uint8_t data);

	bool setData(uint8_t channel, uint8_t data);

	bool setResistance(uint8_t channel, const long resistance);

	uint8_t readControlRegister();
};

#endif // __ad5243_h
