#ifdef __cplusplus
extern "C" {
#endif

#ifndef _LIBCAMERA_H
#define _LIBCAMERA_H

#include <nds.h>

/*!
	\brief Enum of the available cameras.
*/
enum APTINA_CAMERAS 
{
	FRONT = 0x7A, /*!< The DSi's front camera. */
	BACK = 0x78 /*!< The DSi's back camera. */
};

#ifdef ARM7

/*!
	\brief Sets up the camera handler ARM7 side on the specified fifo channel.
	Also sets up initial parameters (for now, only one).
	\param fifo_channel the FIFO channel to listen on.
	\param coarse_int_time coarse integration time (see GBATEK)
*/
void camSetup(int fifo_channel, u8 coarse_int_time);

/*!
	\brief Sets up the camera handler ARM7 side on the specified fifo channel.
	Initial parameters are set to their default values.
	\param fifo_channel the FIFO channel to listen on.
*/
void camSetupDefault(int fifo_channel);

#endif

#ifdef ARM9

/*!
	\brief Syncs with ARM7 through the specified FIFO channel and initializes the specified camera.
	\param fifo_channel the FIFO channel to listen on.
	\param camera the camera to initialize.

	\return 0 if the initialization was successful, -1 if there were errors.
*/
int camInit(int fifo_channel, u8 camera);

/*!
	\brief Fetches a frame from the camera and writes it to the specified buffer via NDMA.
	\param buffer the buffer that will store the frame.
*/
void camFetch(u16* buffer);

/*!
	\brief Deactivates the camera.
*/
void camStop();

/*!
	\brief Switches between the two cameras.
*/
void camSwitch();

#endif

#endif

#ifdef __cplusplus
}
#endif