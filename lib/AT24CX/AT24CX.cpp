#include "AT24CX.h"
#include <Wire.h>

/**
 * Constructor with AT24C32 EEPROM at index 0
 */
AT24CX::AT24CX()
{
	_id = AT24CX_ID | (0 & 0x7); // _addr_at
	_pageSize = 32;							 // AT_PAGE
	Wire.begin();
}

/**
 * Write byte
 */
void AT24CX::write(unsigned int address, byte data)
{
	Wire.beginTransmission(_id);
	if (Wire.endTransmission() == 0)
	{
		Wire.beginTransmission(_id);
		Wire.write(address >> 8);
		Wire.write(address & 0xFF);
		Wire.write(data);
		Wire.endTransmission();
		delay(20);
	}
}

/**
 * Write integer
 */
void AT24CX::writeInt(unsigned int address, unsigned int data)
{
	write(address, (byte *)&data, 2);
}

/**
 * Write sequence of n bytes
 */
void AT24CX::write(unsigned int address, byte *data, int n)
{
	// status quo
	int c = n;		// bytes left to write
	int offD = 0; // current offset in data pointer
	int offP;			// current offset in page
	int nc = 0;		// next n bytes to write

	// write alle bytes in multiple steps
	while (c > 0)
	{
		// calc offset in page
		offP = address % _pageSize;
		// maximal 30 bytes to write
		nc = min(min(c, 30), _pageSize - offP);
		write(address, data, offD, nc);
		c -= nc;
		offD += nc;
		address += nc;
	}
}

/**
 * Read byte
 */
byte AT24CX::read(unsigned int address)
{
	byte b = 0;
	int r = 0;
	Wire.beginTransmission(_id);
	if (Wire.endTransmission() == 0)
	{
		Wire.beginTransmission(_id);
		Wire.write(address >> 8);
		Wire.write(address & 0xFF);
		if (Wire.endTransmission() == 0)
		{
			Wire.requestFrom(_id, 1);
			while (Wire.available() > 0 && r < 1)
			{
				b = (byte)Wire.read();
				r++;
			}
		}
	}
	return b;
}

/**
 * Read integer
 */
unsigned int AT24CX::readInt(unsigned int address)
{
	read(address, _b, 2);
	return *(unsigned int *)&_b[0];
}

/**
 * Read sequence of n bytes
 */
void AT24CX::read(unsigned int address, byte *data, int n)
{
	int c = n;
	int offD = 0;
	// read until are n bytes read
	while (c > 0)
	{
		// read maximal 32 bytes
		int nc = c;
		if (nc > 32)
			nc = 32;
		read(address, data, offD, nc);
		address += nc;
		offD += nc;
		c -= nc;
	}
}
