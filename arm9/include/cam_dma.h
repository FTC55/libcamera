#ifndef _CAM_DMA_H
#define _CAM_DMA_H

#include <nds/ndstypes.h>

//fixed to NDMA1 until libnds implements support for other NDMAs (what else would be using them for now?)
#define NDMA1SAD (*(vu32 *)0x04004120)
#define NDMA1DAD (*(vu32 *)0x04004124)
#define NDMA1TCNT (*(vu32 *)0x04004128)
#define NDMA1WCNT (*(vu32 *)0x0400412C)
#define NDMA1BCNT (*(vu32 *)0x04004130)
#define NDMA1CNT (*(vu32 *)0x04004138)

void camDMAStart(u16 *dest);

#endif