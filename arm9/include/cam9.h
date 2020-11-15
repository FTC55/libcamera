#ifndef _CAM9_H
#define _CAM9_H

#include <nds/ndstypes.h>

#define SCFG_A9ROM (*(vu32 *)0x04004000)
#define SCFG_EXT (*(vu32 *)0x04004008)
#define SCFG_CLK (*(vu32 *)0x04004004)
#define CAM_MCNT (*(vu16 *)0x04004200)
#define CAM_CNT (*(vu16 *)0x04004202)
#define CAM_DAT (*(vu32 *)0x04004204)

#endif