#include "../io_bridge.h"
#include "touchscreen.h"

/****************************************************************************
**  Initialize touch screen controller
****************************************************************************/
void Init_Touch(void)
{
    // Program 6850 and baud rate generator to communcate with touchscreen
    // send touchscreen controller an "enable touch" command
}
    
/****************************************************************************
**  test if screen touched
****************************************************************************/
int ScreenTouched(void) 
{
    // return TRUE if any data received from 6850 connected to touchscreen
    // or FALSE otherwise
}

/****************************************************************************
**  wait for screen to be touched
****************************************************************************/
void WaitForTouch() {
    while(!ScreenTouched())
    ;
}

/* a data type to hold a point/coord */

typedef struct { int x, y; } Point;

/****************************************************************************
**  This function waits for a touch screen press event and returns X,Y coord
****************************************************************************/
Point GetPress(void)
{
    Point p1;

    // wait for a pen down command then return the X,Y coord of the point
    // calibrated correctly so that it maps to a pixel on screen
    
    return p1;
}

/****************************************************************************
**  This function waits for a touch screen release event and returns X,Y coord
****************************************************************************/
Point GetRelease(void)
{
    Point p1;

    // wait for a pen up command then return the X,Y coord of the point
    // calibrated correctly so that it maps to a pixel on screen

    return p1;
}
 
