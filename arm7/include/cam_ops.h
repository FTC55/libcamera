#ifndef _CAM_OPS_H
#define _CAM_OPS_H

#include <nds/ndstypes.h>

#define MCU_ADDRESS 0x098C
#define MCU_DATA 0x0990
#define STANDBY_CNT 0x0018

#define STANDBY_DONE 0x4000

void aptinaInit(u8 camera);

void aptinaActivate();

void aptinaDeactivate();

void aptinaSwitch();

void initParams(u8 coarse_int_time);

#endif