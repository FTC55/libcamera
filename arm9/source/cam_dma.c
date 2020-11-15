#include "cam_dma.h"

void camDMAStart(u16 *dest)
{
    NDMA1SAD = 0x04004204;  //source, atm CAM_DAT
    NDMA1DAD = (u32)dest;   //dest RAM/VRAM
    NDMA1TCNT = 0x00006000; //len for 256x192 total
    NDMA1WCNT = 0x00000200; //len for 256x4 blocks
    NDMA1BCNT = 0x00000002; //timing interval or so
    NDMA1CNT = 0x8B044000;  //start camera DMA

    while (NDMA1TCNT & BIT(31)); //wait for NDMA to be done
}