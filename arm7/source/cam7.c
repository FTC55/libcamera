#include "cam7.h"
#include "cam_ops.h"

#include <nds/fifocommon.h>
#include <nds/ndstypes.h>

#include "libcamera.h"

void camFIFOHandler(u32 value, void *userdata)
{
	int channel = (int)userdata;

	switch (value)
	{
	case 2:
		aptinaActivate();
		fifoSendValue32(channel, 1); //Tell ARM9 we're done so it can continue
		break;

	case 3:
		aptinaDeactivate();
		fifoSendValue32(channel, 1); //Tell ARM9 we're done so it can continue
		break;

	case 4:
		aptinaSwitch();
		fifoSendValue32(channel, 1); //Tell ARM9 we're done so it can continue
		break;

	default:
		aptinaInit(value);
		fifoSendValue32(channel, 1); //Tell ARM9 we're done so it can continue
		break;
	}
}

void camSetup(int fifo_channel, u8 coarse_int_time)
{
	initParams(coarse_int_time);
	fifoSetValue32Handler(fifo_channel, camFIFOHandler, (void *)fifo_channel); //pls don't flog me, it wouldn't dereference correctly if I kept it as an actual pointer
}

void camSetupDefault(int fifo_channel)
{
	camSetup(fifo_channel, 0x10); //default value for coarse_int_time
}
