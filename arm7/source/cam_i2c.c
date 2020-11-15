#include "cam_i2c.h"

#include <nds/bios.h>
#include <nds/arm7/i2c.h>

void writeI2C(u8 device, u16 index, u16 data)
{
	i2cWaitBusy();
	REG_I2CDATA = device; //no flag ORed as we're writing
	REG_I2CCNT = BUSY | START; //no interrupt

	i2cWaitBusy();
	REG_I2CDATA = index >> 8; //MSB
	REG_I2CCNT = BUSY;

	i2cWaitBusy();
	REG_I2CDATA = index & 0xFF; //LSB
	REG_I2CCNT = BUSY;

	i2cWaitBusy();
	REG_I2CDATA = data >> 8; //MSB
	REG_I2CCNT = BUSY;

	i2cWaitBusy();
	REG_I2CDATA = data & 0xFF; //LSB
	REG_I2CCNT = BUSY | STOP;
}

u16 readI2C(u8 device, u16 index)
{
	i2cWaitBusy();
	REG_I2CDATA = device;
	REG_I2CCNT = BUSY | START;

	i2cWaitBusy();
	REG_I2CDATA = index >> 8; //MSB
	REG_I2CCNT = BUSY;

	i2cWaitBusy();
	REG_I2CDATA = index & 0xFF; //LSB
	REG_I2CCNT = BUSY | STOP;

	i2cWaitBusy();
	REG_I2CDATA = device | BIT(0); //this time we issue the read, hence bit0 is ORed in
	REG_I2CCNT = BUSY | START;

	i2cWaitBusy();
	REG_I2CCNT = BUSY | ACK | READ;

	i2cWaitBusy();
	u16 MSB = REG_I2CDATA << 8;
	REG_I2CCNT = BUSY | READ | STOP;

	i2cWaitBusy();
	u16 LSB = REG_I2CDATA;

	return (MSB | LSB);
}

void writeBPTWL(u8 index, u8 data)
{
	i2cWaitBusy();
	REG_I2CDATA = I2C_PM;
	REG_I2CCNT = BUSY | START;
	swiDelay(0x180); //can be decreased, can't be f'd to implement the logic (do tho... or maybe dsis only have the fast one?)

	i2cWaitBusy();
	REG_I2CDATA = index;
	REG_I2CCNT = BUSY;
	swiDelay(0x180);

	i2cWaitBusy();
	REG_I2CDATA = data;
	REG_I2CCNT = BUSY | STOP;
	swiDelay(0x180);
}

u8 readBPTWL(u8 index)
{
	i2cWaitBusy();
	REG_I2CDATA = I2C_PM;
	REG_I2CCNT = BUSY | START;
	swiDelay(0x180);

	i2cWaitBusy();
	REG_I2CDATA = index;
	REG_I2CCNT = BUSY | STOP;
	swiDelay(0x180);

	i2cWaitBusy();
	REG_I2CDATA = I2C_PM | BIT(0); //read bit flag
	REG_I2CCNT = BUSY | START;
	swiDelay(0x180);

	i2cWaitBusy();
	REG_I2CCNT = BUSY | ACK | READ | STOP;
	swiDelay(0x180);

	i2cWaitBusy();
	u8 reading = REG_I2CDATA;

	return (reading);
}