#ifndef _CAM_I2C_H
#define _CAM_I2C_H

#include <nds/ndstypes.h>

#define BUSY 0x80
#define START 0x02
#define STOP 0x01
#define READ 0x20
#define ACK 0x10

void writeI2C(u8 device, u16 index, u16 data);
u16 readI2C(u8 device, u16 index);

void writeBPTWL(u8 index, u8 data);
u8 readBPTWL(u8 index);

#endif