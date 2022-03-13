/* Screen resolution is 800*480 */
#define SCREEN_X_MAX 799
#define SCREEN_y_MAX 479

/*
 * TouchScreen_RXD is connected to GPIO_0[11]
 * TouchScreen_RXD is connected to GPIO_0[10]
 */

/****************************************************************************
**  Initialize touch screen controller
****************************************************************************/
void Init_Touch(void);
    // Program 6850 and baud rate generator to communcate with touchscreen

    // send touchscreen controller an "enable touch" command

/****************************************************************************
**  test if screen touched
****************************************************************************/
int ScreenTouched(void);
    // return TRUE if any data received from 6850 connected to touchscreen
    
    // or FALSE otherwise

/****************************************************************************
**  wait for screen to be touched
****************************************************************************/
void WaitForTouch();

/* a data type to hold a point/coord */

typedef struct { int x, y; } Point;

/****************************************************************************
**  This function waits for a touch screen press event and returns X,Y coord
****************************************************************************/
Point GetPress(void);

/****************************************************************************
**  This function waits for a touch screen release event and returns X,Y coord
****************************************************************************/
Point GetRelease(void);

