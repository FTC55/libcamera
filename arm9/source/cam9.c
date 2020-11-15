#include "cam9.h"
#include "cam_dma.h"

#include <nds/fifocommon.h>
#include <nds/bios.h>
#include <nds/system.h>
#include <stdio.h>

#include "libcamera.h"

int CAM_FIFO_CHANNEL;

void waitForARM7()
{
	//fprintf(stderr, "Waiting for ARM7...\n");
	fifoWaitValue32(CAM_FIFO_CHANNEL);
	//u32 response = fifoGetValue32(CAM_FIFO_CHANNEL);
	fifoGetValue32(CAM_FIFO_CHANNEL);
	//fprintf(stderr, "ARM7> %lX\n", response);
	//fprintf(stderr, "ARM7 done.\n");
}

int camInit(int fifo_channel, u8 camera)
{
	if (!(isDSiMode()))
	{
		fprintf(stderr, "Error: Not running in DSi Mode.");
		return (-1);
	}

	CAM_FIFO_CHANNEL = fifo_channel;

	SCFG_CLK = SCFG_CLK | 0x0004;
	CAM_MCNT = 0x0000;
	swiDelay(0x1E);
	SCFG_CLK = SCFG_CLK | 0x0100;
	swiDelay(0x1E);
	CAM_MCNT = 0x0022;
	swiDelay(0x2008);
	SCFG_CLK = SCFG_CLK & ~(0x0100);
	CAM_CNT = CAM_CNT & ~(0x8000);
	CAM_CNT = CAM_CNT | 0x0020;
	CAM_CNT = (CAM_CNT & ~(0x0300)) | 0x0200;
	CAM_CNT = CAM_CNT | 0x0400;
	CAM_CNT = CAM_CNT | 0x0800;
	SCFG_CLK = SCFG_CLK | 0x0100;
	swiDelay(0x14);

	// issue "aptina_code_list_init" via I2C bus on ARM7 side
	fifoSendValue32(CAM_FIFO_CHANNEL, camera);
	waitForARM7();

	SCFG_CLK = SCFG_CLK & ~(0x0100);
	SCFG_CLK = SCFG_CLK | 0x0100;
	swiDelay(0x14);

	// issue "aptina_code_list_activate" via I2C bus on ARM7 side
	fifoSendValue32(CAM_FIFO_CHANNEL, 2);
	waitForARM7();

	return (0);
}

void camFetch(u16 *buffer)
{
	CAM_CNT = CAM_CNT | 0x2000;
	CAM_CNT = (CAM_CNT & ~(0x000F)) | 0x0003;
	CAM_CNT = CAM_CNT | 0x0020;
	CAM_CNT = CAM_CNT | 0x8000;

	camDMAStart(buffer);
}

void camStop()
{
	fifoSendValue32(CAM_FIFO_CHANNEL, 3); //means deactivate cameras ARM7side
	waitForARM7();
}

void camSwitch()
{
	fifoSendValue32(CAM_FIFO_CHANNEL, 4); //means switch cameras ARM7side
	waitForARM7();
}
