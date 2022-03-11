#include "io_bridge.h"
#include "Touchscreen.h"
#include <stdio.h>
#include <stdlib.h>

static int ReceiverFifo(void)
{
    while (!(*TOUCHSCREEN_VADDR_LineStatusReg & 0x1))
    ;
    return *TOUCHSCREEN_VADDR_ReceiverFifo;
}

/****************************************************************************
**  Initialize touch screen controller
****************************************************************************/
void Init_Touch(void)
{
    // Program 6850 and baud rate generator to communcate with touchscreen
    // send touchscreen controller an "enable touch" command
    *TOUCHSCREEN_VADDR_LineControlReg = 0x80;
    *TOUCHSCREEN_VADDR_DivisorLatchLSB = 0x45;
    *TOUCHSCREEN_VADDR_DivisorLatchMSB = 0x1;
    *TOUCHSCREEN_VADDR_LineControlReg = 0x3;
    *TOUCHSCREEN_VADDR_FifoControlReg = 0x6;
    *TOUCHSCREEN_VADDR_FifoControlReg = 0;
	while(!(*TOUCHSCREEN_VADDR_LineStatusReg & 0x20))
    ;
    *TOUCHSCREEN_VADDR_TransmitterFifo = 0x55;
    while(!(*TOUCHSCREEN_VADDR_LineStatusReg & 0x20))
    ;
    *TOUCHSCREEN_VADDR_TransmitterFifo = 0x1;
    while(!(*TOUCHSCREEN_VADDR_LineStatusReg & 0x20))
    ;
    *TOUCHSCREEN_VADDR_TransmitterFifo = 0x12;
}
    
/****************************************************************************
**  test if screen touched
****************************************************************************/
int ScreenTouched(void) 
{
    // return TRUE if any data received from 6850 connected to touchscreen
    // or FALSE otherwise
    return *TOUCHSCREEN_VADDR_ReceiverFifo & 0x1;
}

/****************************************************************************
**  wait for screen to be touched
****************************************************************************/
void WaitForTouch() {
    while(!ScreenTouched())
    ;
}

/* a data type to hold a point/coord */

/****************************************************************************
**  This function waits for a touch screen press event and returns X,Y coord
****************************************************************************/
Point GetPress(void)
{
    // wait for a pen down command then return the X,Y coord of the point
    // calibrated correctly so that it maps to a pixel on screen
	Point p;
	WaitForTouch();
	while((ReceiverFifo() & 0x81) != 0x81) //wait for pen down command
		;
	p.x = ReceiverFifo() | (ReceiverFifo() << 7) * SCREEN_X_MAX/4096;
	p.y = ReceiverFifo() | (ReceiverFifo() << 7) * SCREEN_y_MAX/4096;
	return p;
}

/****************************************************************************
**  This function waits for a touch screen release event and returns X,Y coord
****************************************************************************/
Point GetRelease(void)
{
    // wait for a pen up command then return the X,Y coord of the point
    // calibrated correctly so that it maps to a pixel on screen
	Point p;
	WaitForTouch();
	while((ReceiverFifo() & 0x81) != 0x80) //wait for pen down command
		;
	p.x = ReceiverFifo() | (ReceiverFifo() << 7) * SCREEN_X_MAX/4096;
	p.y = ReceiverFifo() | (ReceiverFifo() << 7) * SCREEN_y_MAX/4096;
	return p;
}
 
