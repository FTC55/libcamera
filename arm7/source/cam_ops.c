#include "cam_ops.h"
#include "cam_i2c.h"

#include "libcamera.h"

u8 ACTIVE_CAM;
u8 COARSE_INTEGRATION_TIME;

void setApt(u16 index, u16 data)
{
	u16 current = readI2C(ACTIVE_CAM, index);
	writeI2C(ACTIVE_CAM, index, current | data);
}

void clrApt(u16 index, u16 data)
{
	u16 current = readI2C(ACTIVE_CAM, index);
	writeI2C(ACTIVE_CAM, index, current & ~(data));
}

void waitClrApt(u16 reg, u16 mask)
{
	while (readI2C(ACTIVE_CAM, reg) & mask); //evaluates true whenever a bit is set
}

void waitSetApt(u16 reg, u16 mask)
{
	while (!(readI2C(ACTIVE_CAM, reg) & mask)); // evaluates true whenever a bit is clear
}

void writeMCU(u16 index, u16 data)
{
	writeI2C(ACTIVE_CAM, MCU_ADDRESS, index);
	writeI2C(ACTIVE_CAM, MCU_DATA, data);
}

u16 readMCU(u16 index)
{
	writeI2C(ACTIVE_CAM, MCU_ADDRESS, index);
	u16 read = readI2C(ACTIVE_CAM, MCU_DATA);
	return (read);
}

void setMCU(u16 index, u16 data)
{
	u16 current = readMCU(index);
	writeMCU(index, current | data);
}

void waitClrMCU(u16 reg, u16 mask)
{
	while (readMCU(reg) & mask); //evaluates true whenever a bit is set
}

void aptinaInit(u8 camera) //might want to init both at the same time instead as NO$ suggests, TODO
{
	for (u8 device = BACK; device <= FRONT; device += 0x02) //hacky but u get the point lol
	{
		ACTIVE_CAM = device;
		writeI2C(ACTIVE_CAM, 0x001A, 0x0003);
		writeI2C(ACTIVE_CAM, 0x001A, 0x0000);
		writeI2C(ACTIVE_CAM, 0x0018, 0x4028);
		writeI2C(ACTIVE_CAM, 0x001E, 0x0201);
		writeI2C(ACTIVE_CAM, 0x0016, 0x42DF);
		waitClrApt(0x0018, 0x4000);
		waitSetApt(0x301A, 0x0004);
		writeMCU(0x02F0, 0x0000);
		writeMCU(0x02F2, 0x0210);
		writeMCU(0x02F4, 0x001A);
		writeMCU(0x2145, 0x02F4);
		writeMCU(0xA134, 0x0001);
		setMCU(0xA115, 0x0002);
		writeMCU(0x2755, 0x0002);
		writeMCU(0x2757, 0x0002);
		writeI2C(ACTIVE_CAM, 0x0014, 0x2145);
		writeI2C(ACTIVE_CAM, 0x0010, 0x0111);
		writeI2C(ACTIVE_CAM, 0x0012, 0x0000);
		writeI2C(ACTIVE_CAM, 0x0014, 0x244B);
		writeI2C(ACTIVE_CAM, 0x0014, 0x304B);
		waitSetApt(0x0014, 0x8000);
		clrApt(0x0014, 0x0001);
		writeMCU(0x2703, 0x0100);
		writeMCU(0x2705, 0x00C0);
		writeMCU(0x2707, 0x0280);
		writeMCU(0x2709, 0x01E0);
		writeMCU(0x2715, 0x0001);
		writeMCU(0x2719, 0x001A);
		writeMCU(0x271B, 0x006B);
		writeMCU(0x271D, 0x006B);
		writeMCU(0x271F, 0x02C0);
		writeMCU(0x2721, 0x034B);
		writeMCU(0xA20B, 0x0000);
		writeMCU(0xA20C, 0x0006);
		writeMCU(0x272B, 0x0001);
		writeMCU(0x272F, 0x001A);
		writeMCU(0x2731, 0x006B);
		writeMCU(0x2733, 0x006B);
		writeMCU(0x2735, 0x02C0);
		writeMCU(0x2737, 0x034B);
		setApt(0x3210, 0x0008);
		writeMCU(0xA208, 0x0000);
		writeMCU(0xA24C, 0x0020);
		writeMCU(0xA24F, 0x0070);
		if (ACTIVE_CAM == FRONT)
		{
			writeMCU(0x2717, 0x0024);
			writeMCU(0x272D, 0x0024);
		}
		else
		{
			writeMCU(0x2717, 0x0025);
			writeMCU(0x272D, 0x0025);
		}
		if (ACTIVE_CAM == FRONT)
		{
			writeMCU(0xA202, 0x0022);
			writeMCU(0xA203, 0x00BB);
		}
		else
		{
			writeMCU(0xA202, 0x0000);
			writeMCU(0xA203, 0x00FF);
		}
		setApt(0x0016, 0x0020);
		writeMCU(0xA115, 0x0072);
		writeMCU(0xA11F, 0x0001);
		if (ACTIVE_CAM == FRONT)
		{
			writeI2C(ACTIVE_CAM, 0x326C, 0x0900);
			writeMCU(0xAB22, 0x0001);
		}
		else
		{
			writeI2C(ACTIVE_CAM, 0x326C, 0x1000);
			writeMCU(0xAB22, 0x0002);
		}
		writeMCU(0xA103, 0x0006);
		waitClrMCU(0xA103, 0x000F);
		writeMCU(0xA103, 0x0005);
		waitClrMCU(0xA103, 0x000F);

		//for reasons that are way beyond me, if I don't do this then the image gets messed up. RIP all of my color translation code. (mostly same code as aptinaDeactivate)
		clrApt(0x001A, 0x0200);
		setApt(0x0018, 0x0001);
		waitSetApt(0x0018, 0x4000);
		waitClrApt(0x301A, 0x0004);
	}

	ACTIVE_CAM = camera; //we set the current camera to the one specified
	return;
}

void aptinaActivate()
{
	clrApt(0x0018, 0x0001);
	waitClrApt(0x0018, 0x4000);
	waitSetApt(0x301A, 0x0004);
	writeI2C(ACTIVE_CAM, 0x3012, COARSE_INTEGRATION_TIME);
	setApt(0x001A, 0x0200);

	if (ACTIVE_CAM == BACK)
	{
		writeBPTWL(I2CREGPM_CAMLED, 0x00); //for some odd reason, this turns the LED ON and 0x01 turns it off? check BPTWL write logic
	}

	return;
}

void aptinaDeactivate()
{
	clrApt(0x001A, 0x0200);
	setApt(0x0018, 0x0001);
	waitSetApt(0x0018, 0x4000);
	waitClrApt(0x301A, 0x0004);

	if (ACTIVE_CAM == BACK)
	{
		writeBPTWL(I2CREGPM_CAMLED, 0x01); //ditto
	}
}

void aptinaSwitch()
{
	if (ACTIVE_CAM == BACK)
	{
		aptinaDeactivate();
		ACTIVE_CAM = FRONT;
		aptinaActivate();
	}
	else
	{
		aptinaDeactivate();
		ACTIVE_CAM = BACK;
		aptinaActivate();
	}
}

void initParams(u8 coarse_int_time)
{ //called from ARM7 at setup
	COARSE_INTEGRATION_TIME = coarse_int_time;
}