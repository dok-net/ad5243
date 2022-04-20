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

#include <Wire.h>

#define AD5243_I2C_ADDRESS 0x2c

class AD5243
{
private:
	uint8_t _address;
	TwoWire &_i2cPort;
	long _resistance;
	long _total_resistance;

public:
	uint32_t channel1Resistance;
	uint32_t channel2Resistance;

	AD5243(long total_resistance, TwoWire &wirePort = Wire) : _i2cPort(wirePort)
	{
		_total_resistance = total_resistance;
	}

	bool begin(uint8_t address = AD5243_I2C_ADDRESS)
	{
		_address = address;
		return connected();
	}

	bool connected();

	bool setResistance(uint8_t channel, long resistance);

	uint8_t readControlRegister();
};
