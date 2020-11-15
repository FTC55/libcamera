#include <nds.h>
#include <stdio.h>
#include <libcamera.h>

int main(void) {
	videoSetMode(MODE_5_2D);
	vramSetBankA(VRAM_A_MAIN_BG_0x06040000);
	consoleDemoInit();

	//initialize the buffer
	int bg = bgInit(2, BgType_Bmp16, BgSize_B16_256x256, 16,0); //going to VRAM_A

	//get a pointer to the buffer
	u16* bgmem = (u16*)bgGetGfxPtr(bg);

	//initialize the camera
	camInit(FIFO_USER_01, BACK);

	while(1) {

		//fetch a frame and write it to the active background, displaying it to the screen
		camFetch(bgmem);
		//wait for the next VBlank to repeat
		swiWaitForVBlank();
		
		scanKeys();
		if (keysDown() & KEY_B) { //switch cameras whenever the B button is pressed
			camSwitch();
		}
		if (keysDown() & KEY_START) { //deactivate the camera and terminate the program whenever START is pressed
			camStop();
			break;
		}
	}

	return 0;
}

