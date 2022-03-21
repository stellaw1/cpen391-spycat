#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "../../io_bridge.c"
#include "../../touchscreen/Touchscreen.c"

#include "GraphicsRoutines.h"
#include "Colours.h"
#include "ColourPallette.c"

#define XRES 800
#define YRES 480

#define DrawHLine		1
#define DrawVLine		2
#define DrawLine		3
#define PutAPixel		0xA
#define GetAPixel		0xB
#define ProgramPaletteColour   	0x10

/*******************************************************************************************
** This macro pauses until the graphics chip status register indicates that it is idle
*******************************************************************************************/

void WAIT_FOR_GRAPHICS(void) {
	while ((*GraphicsStatusReg & 0x0001) != 0x0001);
}

int init_graphics(void) {
	// Program the palette for the GUI
	// DE1 can only display 64 at any one time
	int c;
	for(c = 0; c < 64; c++) { // DE1 can only display 64 at any one time
		ProgramPalette(c, ColourPalletteData[c]);
	}
	return 1;
}

// the header file "Colours.h" contains symbolic names for all 256 colours e.g. RED
// while the source file ColourPaletteData.c contains the 24 bit RGB data
// that is pre-programmed into each of the 256 palettes

/**********************************************************************
* This function writes a single pixel to the x,y coords specified in the specified colour
* Note colour is a palette number (0-255) not a 24 bit RGB value
**********************************************************************/
void WriteAPixel (int x, int y, int Colour)
{
	WAIT_FOR_GRAPHICS();			// is graphics ready for new command

	*GraphicsX1Reg = x;			// write coords to x1, y1
	*GraphicsY1Reg = y;
	*GraphicsColourReg = Colour;		// set pixel colour with a palette number
	*GraphicsCommandReg = PutAPixel;		// give graphics a "write pixel" command
}

/*****************************************************************************************
* This function read a single pixel from x,y coords specified and returns its colour
* Note returned colour is a palette number (0-255) not a 24 bit RGB value
******************************************************************************************/
int ReadAPixel (int x, int y)
{
	WAIT_FOR_GRAPHICS();			// is graphics ready for new command

	*GraphicsX1Reg = x;			// write coords to x1, y1
	*GraphicsY1Reg = y;
	*GraphicsCommandReg = GetAPixel;		// give graphics a "get pixel" command

	WAIT_FOR_GRAPHICS();			// is graphics done reading pixel
	return (int)(*GraphicsColourReg) ;		// return the palette number (colour)
}

/****************************************************************************************************
** subroutine to program a hardware (graphics chip) palette number with an RGB value
** e.g. ProgramPalette(RED, 0x00FF0000) ;
****************************************************************************************************/

void ProgramPalette(int PaletteNumber, int RGB)
{
    WAIT_FOR_GRAPHICS();
    *GraphicsColourReg = PaletteNumber;
    *GraphicsX1Reg = RGB >> 16   ;          // program red value in ls.8 bit of X1 reg
    *GraphicsY1Reg = RGB ;                	 // program green and blue into 16 bit of Y1 reg
    *GraphicsCommandReg = ProgramPaletteColour;	// issue command
}

void clear_screen() {
	int i, j;
	for (i = 0; i < YRES; i++) {
        for (j = 0; j < XRES; j++) {
            WriteAPixel(j, i, BLACK);
        }
	}
}