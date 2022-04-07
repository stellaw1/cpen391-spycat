/* Screen resolution is 800*480 */
#define SCREEN_X_MAX 479
#define SCREEN_Y_MAX 799

#define NULL_RETURN_X -100
#define NULL_RETURN_Y -200

#define SLEEP_TIMEOUT 4

/*
 * TouchScreen_RXD is connected to GPIO_0[11]
 * TouchScreen_RXD is connected to GPIO_0[10]
 */

/****************************************************************************
**  Initialize touch screen controller
****************************************************************************/
int Init_Touch(void);
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

typedef struct
{
    int x, y;
} Point;

/****************************************************************************
**  This function waits for a touch screen press event and returns X,Y coord
****************************************************************************/
Point GetPress(void);

/****************************************************************************
**  This function waits for a touch screen release event and returns X,Y coord
****************************************************************************/
Point GetRelease(void);

/****************************************************************************
**  This function waits for a touch screen release event and returns X,Y coord
**  while keeping a timer
****************************************************************************/
Point GetReleaseTimer(void);
