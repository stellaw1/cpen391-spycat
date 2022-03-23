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
#include "Fonts.c"

#define XRES 800
#define YRES 480
#define FONT2_XPIXELS	10				// width of Font2 characters in pixels (no spacing)
#define FONT2_YPIXELS	14				// height of Font2 characters in pixels (no spacing)

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

////////////////////////////////////////////////////////////////////////////////////////
// Print characters on VGA screen.
////////////////////////////////////////////////////////////////////////////////////////
extern const unsigned char Font5x7[][7] ;
extern const unsigned short int Font10x14[][14] ;

void OutGraphicsCharFont1(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase)
{
// using register variables (as opposed to stack based ones) may make execution faster
// depends on compiler and CPU

	register int row, column, theX = x, theY = y ;
	register int pixels ;
	register char theColour = fontcolour  ;
	register int BitMask, theC = c ;

// if x,y coord off edge of screen don't bother

    if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))
        return ;


// if printable character subtract hex 20
	if(((short)(theC) >= (short)(' ')) && ((short)(theC) <= (short)('~'))) {
		theC = theC - 0x20 ;
		for(row = 0; (char)(row) < (char)(7); row ++)	{

// get the bit pattern for row 0 of the character from the software font
			pixels = Font5x7[theC][row] ;
			BitMask = 16 ;

			for(column = 0; (char)(column) < (char)(5); column ++)	{

// if a pixel in the character display it
				if((pixels & BitMask))
					WriteAPixel(theX+column, theY+row, theColour) ;

				else {
					if(Erase == 1)

// if pixel is part of background (not part of character)
// erase the background to value of variable BackGroundColour

						WriteAPixel(theX+column, theY+row, backgroundcolour) ;
				}
				BitMask = BitMask >> 1 ;
			}
		}
	}
}

/******************************************************************************************************************************
** This function draws a single ASCII character at the coord specified using the colour specified
** OutGraphicsCharFont2(100,100, RED, 'A', TRUE, FALSE, 1, 1) ;	// display upper case 'A' in RED at coords 100,100, erase background
** no scroll, scale x,y= 1,1
**
******************************************************************************************************************************/
void OutGraphicsCharFont2(int x, int y, int colour, int backgroundcolour, int c, int Erase)
{
	register int 	row,
					column,
					theX = x,
					theY = y ;
	register int 	pixels ;
	register char 	theColour = colour  ;
	register int 	BitMask,
					theCharacter = c,
					j,
					theRow, theColumn;


    if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))  // if start off edge of screen don't bother
        return ;

	if(((short)(theCharacter) >= (short)(' ')) && ((short)(theCharacter) <= (short)('~'))) {			// if printable character
		theCharacter -= 0x20 ;																			// subtract hex 20 to get index of first printable character (the space character)
		theRow = FONT2_YPIXELS;
		theColumn = FONT2_XPIXELS;

		for(row = 0; row < theRow ; row ++)	{
			pixels = Font10x14[theCharacter][row] ;		     								// get the pixels for row 0 of the character to be displayed
			BitMask = 512 ;							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
			for(column = 0; column < theColumn;   )  	{
				if((pixels & BitMask))														// if valid pixel, then write it
					WriteAPixel(theX+column, theY+row, theColour) ;
				else {																		// if not a valid pixel, do we erase or leave it along (no erase)
					if(Erase == 1)
						WriteAPixel(theX+column, theY+row, backgroundcolour) ;
					// else leave it alone
				}
					column ++ ;
				BitMask = BitMask >> 1 ;
			}
		}
	}
}

/*
 * Print sentence on screen
 */
void GraphicsString(char *string_input, int x, int y, int colour, int background)
{
	//printf("%s", string_input);
	int i = 0;
	while(string_input[i]!='\0') {
		//printf("%c", string_input[i]);
		OutGraphicsCharFont2(x+i*15, y, colour, background, string_input[i], 1);
		i++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////
// Print lines and boxes on VGA screen.
////////////////////////////////////////////////////////////////////////////////////////
void horizontal_line(int x1, int y1, int length, int Colour) {
	int i;
	for(i = 0; i < length; i++){
		WriteAPixel (x1 + i, y1, Colour);
	}
}

void vertical_line(int x1, int y1, int length, int Colour) {
	int i;
	for(i = 0; i < length; i++){
		horizontal_line(x1, y1+i, 1, Colour);
	}
}

void box_empty(int x1, int y1, int width, int height, int Colour) {
	int i;
	horizontal_line(x1, y1, width, Colour);
	horizontal_line(x1, y1 + height, width, Colour);
	vertical_line(x1, y1, height, Colour);
	vertical_line(x1 + width, y1, height, Colour);
}

void box_filled(int x1, int y1, int width, int height, int Colour) {
	int i;
	for(i = 0; i < height; i++){
		horizontal_line(x1, y1+i, width, Colour);
	}
}

void text_box_filled(char *string_input, int x1, int y1, int text_x, int text_y, int width, int height, int font_colour, int Colour) {
	box_filled(x1, y1, width, height, Colour);
	GraphicsString(string_input, text_x, text_y, font_colour, Colour);
}

void keyboard (void) {
	//keyboard background
	int keyColour = GRAY;
	int fontColour = WHITE;
	box_filled(0,239,800,240,DARK_SLATE_GRAY);
	//1st line ~ 1 2 3 4 5 6 7 8 9 0 - + backspace
	int i = 50+3;
	text_box_filled("~", 0+4, 239+8, 0+4+17, 239+8+16, 50, 40, fontColour, keyColour);
	text_box_filled("1", 0+4+i, 239+8, 0+4+i+17, 239+8+16, 50, 40, fontColour, keyColour);
	text_box_filled("2", 0+4+i*2, 239+8, 0+4+i*2+17, 239+8+16, 50, 40, fontColour, keyColour);
	text_box_filled("3", 0+4+i*3, 239+8, 0+4+i*3+17, 239+8+16, 50, 40, fontColour, keyColour);
	text_box_filled("4", 0+4+i*4, 239+8, 0+4+i*4+17, 239+8+16, 50, 40, fontColour, keyColour);
	text_box_filled("5", 0+4+i*5, 239+8, 0+4+i*5+17, 239+8+16, 50, 40, fontColour, keyColour);
	text_box_filled("6", 0+4+i*6, 239+8, 0+4+i*6+17, 239+8+16, 50, 40, fontColour, keyColour);
	text_box_filled("7", 0+4+i*7, 239+8, 0+4+i*7+17, 239+8+16, 50, 40, fontColour, keyColour);
	text_box_filled("8", 0+4+i*8, 239+8, 0+4+i*8+17, 239+8+16, 50, 40, fontColour, keyColour);
	text_box_filled("9", 0+4+i*9, 239+8, 0+4+i*9+17, 239+8+16, 50, 40, fontColour, keyColour);
	text_box_filled("0", 0+4+i*10, 239+8, 0+4+i*10+17, 239+8+16, 50, 40, fontColour, keyColour);
	text_box_filled("-", 0+4+i*11, 239+8, 0+4+i*11+17, 239+8+16, 50, 40, fontColour, keyColour);
	text_box_filled("+", 0+4+i*12, 239+8, 0+4+i*12+17, 239+8+16, 50, 40, fontColour, keyColour);
	text_box_filled("delete", 0+4+i*13, 239+8, 0+4+i*13+14, 239+8+16, 100, 40, fontColour, keyColour);
	//2nd line q w e r t y u i o p _ = [ ]
	text_box_filled("Q", 0+29, 239+8+6+40, 0+29+17, 239+8+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("W", 0+29+i, 239+8+6+40, 0+29+17+i, 239+8+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("E", 0+29+i*2, 239+8+6+40, 0+29+17+i*2, 239+8+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("R", 0+29+i*3, 239+8+6+40, 0+29+17+i*3, 239+8+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("T", 0+29+i*4, 239+8+6+40, 0+29+17+i*4, 239+8+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("Y", 0+29+i*5, 239+8+6+40, 0+29+17+i*5, 239+8+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("U", 0+29+i*6, 239+8+6+40, 0+29+17+i*6, 239+8+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("I", 0+29+i*7, 239+8+6+40, 0+29+17+i*7, 239+8+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("O", 0+29+i*8, 239+8+6+40, 0+29+17+i*8, 239+8+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("P", 0+29+i*9, 239+8+6+40, 0+29+17+i*9, 239+8+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("_", 0+29+i*10, 239+8+6+40, 0+29+17+i*10, 239+8+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("=", 0+29+i*11, 239+8+6+40, 0+29+17+i*11, 239+8+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("[", 0+29+i*12, 239+8+6+40, 0+29+17+i*12, 239+8+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("]", 0+29+i*13, 239+8+6+40, 0+29+17+i*13, 239+8+6+40+16, 50, 40, fontColour, keyColour);
	//3rd line A S D F G H J K L { } : ;
	text_box_filled("A", 0+58+i*0, 239+8+6+40+6+40, 0+58+17+i*0, 239+8+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("S", 0+58+i*1, 239+8+6+40+6+40, 0+58+17+i*1, 239+8+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("D", 0+58+i*2, 239+8+6+40+6+40, 0+58+17+i*2, 239+8+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("F", 0+58+i*3, 239+8+6+40+6+40, 0+58+17+i*3, 239+8+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("G", 0+58+i*4, 239+8+6+40+6+40, 0+58+17+i*4, 239+8+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("H", 0+58+i*5, 239+8+6+40+6+40, 0+58+17+i*5, 239+8+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("J", 0+58+i*6, 239+8+6+40+6+40, 0+58+17+i*6, 239+8+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("K", 0+58+i*7, 239+8+6+40+6+40, 0+58+17+i*7, 239+8+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("L", 0+58+i*8, 239+8+6+40+6+40, 0+58+17+i*8, 239+8+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("{", 0+58+i*9, 239+8+6+40+6+40, 0+58+17+i*9, 239+8+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("}", 0+58+i*10, 239+8+6+40+6+40, 0+58+17+i*10, 239+8+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled(":", 0+58+i*11, 239+8+6+40+6+40, 0+58+17+i*11, 239+8+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled(";", 0+58+i*12, 239+8+6+40+6+40, 0+58+17+i*12, 239+8+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("<", 0+58+i*13, 239+8+6+40+6+40, 0+58+17+i*13, 239+8+6+40+6+40+16, 50, 40, fontColour, keyColour);
	//4th line Z X C V B N M > , . ? / !
	text_box_filled("Z", 0+87+i*0, 239+8+6+40+6+40+6+40, 0+87+17+i*0, 239+8+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("X", 0+87+i*1, 239+8+6+40+6+40+6+40, 0+87+17+i*1, 239+8+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("C", 0+87+i*2, 239+8+6+40+6+40+6+40, 0+87+17+i*2, 239+8+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("V", 0+87+i*3, 239+8+6+40+6+40+6+40, 0+87+17+i*3, 239+8+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("B", 0+87+i*4, 239+8+6+40+6+40+6+40, 0+87+17+i*4, 239+8+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("N", 0+87+i*5, 239+8+6+40+6+40+6+40, 0+87+17+i*5, 239+8+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("M", 0+87+i*6, 239+8+6+40+6+40+6+40, 0+87+17+i*6, 239+8+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled(">", 0+87+i*7, 239+8+6+40+6+40+6+40, 0+87+17+i*7, 239+8+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled(",", 0+87+i*8, 239+8+6+40+6+40+6+40, 0+87+17+i*8, 239+8+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled(".", 0+87+i*9, 239+8+6+40+6+40+6+40, 0+87+17+i*9, 239+8+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("?", 0+87+i*10, 239+8+6+40+6+40+6+40, 0+87+17+i*10, 239+8+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("/", 0+87+i*11, 239+8+6+40+6+40+6+40, 0+87+17+i*11, 239+8+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("!", 0+87+i*12, 239+8+6+40+6+40+6+40, 0+87+17+i*12, 239+8+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	//5th line @ # $ space % ^ & * ( )
	text_box_filled("@", 0+4+i*0, 239+8+6+40+6+40+6+40+6+40, 0+4+17+i*0, 239+8+6+40+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("#", 0+4+i*1, 239+8+6+40+6+40+6+40+6+40, 0+4+17+i*1, 239+8+6+40+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("$", 0+4+i*2, 239+8+6+40+6+40+6+40+6+40, 0+4+17+i*2, 239+8+6+40+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("%", 0+4+i*3, 239+8+6+40+6+40+6+40+6+40, 0+4+17+i*3, 239+8+6+40+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("space", 0+4+i*4, 239+8+6+40+6+40+6+40+6+40, 0+4+17+105+i*4, 239+8+6+40+6+40+6+40+6+40+16, 300, 40, fontColour, keyColour);
	text_box_filled("^", 0+4+300+3+i*4, 239+8+6+40+6+40+6+40+6+40, 0+4+17+300+3+i*4, 239+8+6+40+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("&", 0+4+300+3+i*5, 239+8+6+40+6+40+6+40+6+40, 0+4+17+300+3+i*5, 239+8+6+40+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("*", 0+4+300+3+i*6, 239+8+6+40+6+40+6+40+6+40, 0+4+17+300+3+i*6, 239+8+6+40+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled("(", 0+4+300+3+i*7, 239+8+6+40+6+40+6+40+6+40, 0+4+17+300+3+i*7, 239+8+6+40+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
	text_box_filled(")", 0+4+300+3+i*8, 239+8+6+40+6+40+6+40+6+40, 0+4+17+300+3+i*8, 239+8+6+40+6+40+6+40+6+40+16, 50, 40, fontColour, keyColour);
}
int keyboard_helper (int x, int y, Point p) {
	if(p.y >= x && p.y <= x + 50 && p.x >= y && p.x <= y + 40){
		return 1;
	} else return 0;
}
/*
 (0,239)
 ____________________________________________
 |                   8
 | _________50_____________    ______________
 | |                       |  |
 |4|                       | 3|
 | |          ~            |  |
 | 40                      40 |
 | |                       |  |
 | |________50_____________|  |_______________
 |                         6   
 |               _______50______________    __
 |      29      |                       |  |
*/
char keyboard_response (void) {
	Point p;
	while(1){
		p = GetPress();
		int x = p.y;
		int y = p.x;
		//TODO add region detection
		int key_width = 50;
		int key_height = 40;
		int topleft = 239;
		//1st line
		if (keyboard_helper(4+53*0, 239+8, p)){
			printf("~");
			return '~';
		}
		if (keyboard_helper(4+53*1, 239+8, p)){
			printf("1");
			return '1';
		}
		if (keyboard_helper(4+53*2, 239+8, p)){
			printf("2");
			return '2';
		}
		if (keyboard_helper(4+53*3, 239+8, p)){
			printf("3");
			return '3';
		}
		if (keyboard_helper(4+53*4, 239+8, p)){
			printf("4");
			return '4';
		}
		if (keyboard_helper(4+53*5, 239+8, p)){
			printf("5");
			return '5';
		}
		if (keyboard_helper(4+53*6, 239+8, p)){
			printf("6");
			return '6';
		}
		if (keyboard_helper(4+53*7, 239+8, p)){
			printf("7");
			return '7';
		}
		if (keyboard_helper(4+53*8, 239+8, p)){
			printf("8");
			return '8';
		}
		if (keyboard_helper(4+53*9, 239+8, p)){
			printf("9");
			return '9';
		}
		if (keyboard_helper(4+53*10, 239+8, p)){
			printf("0");
			return '0';
		}
		if (keyboard_helper(4+53*11, 239+8, p)){
			printf("-");
			return '-';
		}
		if (keyboard_helper(4+53*12, 239+8, p)){
			printf("+");
			return '+';
		}
		if (keyboard_helper(4+53*13, 239+8, p)){
			printf("delete");
			return '`';
		}
		if (keyboard_helper(4+53*14, 239+8, p)){
			printf("delete");
			return '`';
		}

		//2nd line
		if (keyboard_helper(29+53*0, 239+8+40+6, p)){
			printf("Q");
			return 'Q';
		}
		if (keyboard_helper(29+53*1, 239+8+40+6, p)){
			printf("W");
			return 'W';
		}
		if (keyboard_helper(29+53*2, 239+8+40+6, p)){
			printf("E");
			return 'E';
		}
		if (keyboard_helper(29+53*3, 239+8+40+6, p)){
			printf("R");
			return 'R';
		}
		if (keyboard_helper(29+53*4, 239+8+40+6, p)){
			printf("T");
			return 'T';
		}
		if (keyboard_helper(29+53*5, 239+8+40+6, p)){
			printf("Y");
			return 'Y';
		}
		if (keyboard_helper(29+53*6, 239+8+40+6, p)){
			printf("U");
			return 'U';
		}
		if (keyboard_helper(29+53*7, 239+8+40+6, p)){
			printf("I");
			return 'I';
		}
		if (keyboard_helper(29+53*8, 239+8+40+6, p)){
			printf("O");
			return 'O';
		}
		if (keyboard_helper(29+53*9, 239+8+40+6, p)){
			printf("P");
			return 'P';
		}
		if (keyboard_helper(29+53*10, 239+8+40+6, p)){
			printf("_");
			return '_';
		}
		if (keyboard_helper(29+53*11, 239+8+40+6, p)){
			printf("=");
			return '=';
		}
		if (keyboard_helper(29+53*12, 239+8+40+6, p)){
			printf("[");
			return '[';
		}
		if (keyboard_helper(29+53*13, 239+8+40+6, p)){
			printf("]");
			return ']';
		}

		//3rd line
		if (keyboard_helper(58+53*0, 239+8+40+6+40+6, p)){
			printf("A");
			return 'A';
		}
		if (keyboard_helper(58+53*1, 239+8+40+6+40+6, p)){
			printf("S");
			return 'S';
		}
		if (keyboard_helper(58+53*2, 239+8+40+6+40+6, p)){
			printf("D");
			return 'D';
		}
		if (keyboard_helper(58+53*3, 239+8+40+6+40+6, p)){
			printf("F");
			return 'F';
		}
		if (keyboard_helper(58+53*4, 239+8+40+6+40+6, p)){
			printf("G");
			return 'G';
		}
		if (keyboard_helper(58+53*5, 239+8+40+6+40+6, p)){
			printf("H");
			return 'H';
		}
		if (keyboard_helper(58+53*6, 239+8+40+6+40+6, p)){
			printf("J");
			return 'J';
		}
		if (keyboard_helper(58+53*7, 239+8+40+6+40+6, p)){
			printf("K");
			return 'K';
		}
		if (keyboard_helper(58+53*8, 239+8+40+6+40+6, p)){
			printf("L");
			return 'L';
		}
		if (keyboard_helper(58+53*9, 239+8+40+6+40+6, p)){
			printf("{");
			return '{';
		}
		if (keyboard_helper(58+53*10, 239+8+40+6+40+6, p)){
			printf("}");
			return '}';
		}
		if (keyboard_helper(58+53*11, 239+8+40+6+40+6, p)){
			printf(":");
			return ':';
		}if (keyboard_helper(58+53*12, 239+8+40+6+40+6, p)){
			printf(";");
			return ';';
		}
		if (keyboard_helper(58+53*13, 239+8+40+6+40+6, p)){
			printf("<");
			return '<';
		}
		//4th line
		if (keyboard_helper(87+53*0, 239+8+40+6+40+6+40+6, p)){
			printf("Z");
			return 'Z';
		}
		if (keyboard_helper(87+53*1, 239+8+40+6+40+6+40+6, p)){
			printf("X");
			return 'X';
		}
		if (keyboard_helper(87+53*2, 239+8+40+6+40+6+40+6, p)){
			printf("C");
			return 'C';
		}
		if (keyboard_helper(87+53*3, 239+8+40+6+40+6+40+6, p)){
			printf("V");
			return 'V';
		}
		if (keyboard_helper(87+53*4, 239+8+40+6+40+6+40+6, p)){
			printf("B");
			return 'B';
		}
		if (keyboard_helper(87+53*5, 239+8+40+6+40+6+40+6, p)){
			printf("N");
			return 'N';
		}
		if (keyboard_helper(87+53*6, 239+8+40+6+40+6+40+6, p)){
			printf("M");
			return 'M';
		}
		if (keyboard_helper(87+53*7, 239+8+40+6+40+6+40+6, p)){
			printf(">");
			return '>';
		}
		if (keyboard_helper(87+53*8, 239+8+40+6+40+6+40+6, p)){
			printf(",");
			return ',';
		}		
		if (keyboard_helper(87+53*9, 239+8+40+6+40+6+40+6, p)){
			printf(".");
			return '.';
		}
		if (keyboard_helper(87+53*10, 239+8+40+6+40+6+40+6, p)){
			printf("?");
			return '?';
		}
		if (keyboard_helper(87+53*11, 239+8+40+6+40+6+40+6, p)){
			printf("/");
			return '/';
		}
		if (keyboard_helper(87+53*12, 239+8+40+6+40+6+40+6, p)){
			printf("!");
			return '!';
		}
		//5th line
		if (keyboard_helper(4+53*0, 239+8+40+6+40+6+40+6+40+6, p)){
			printf("@");
			return '@';
		}
		if (keyboard_helper(4+53*1, 239+8+40+6+40+6+40+6+40+6, p)){
			printf("#");
			return '#';
		}
		if (keyboard_helper(4+53*2, 239+8+40+6+40+6+40+6+40+6, p)){
			printf("$");
			return '$';
		}
		if (keyboard_helper(4+53*3, 239+8+40+6+40+6+40+6+40+6, p)){
			printf("%%");
			return '%';
		}
		//space 1
		if (keyboard_helper(4+53*4, 239+8+40+6+40+6+40+6+40+6, p)){
			printf("space");
			return ' ';
		}
		//space 2
		if (keyboard_helper(4+53*4+50*1, 239+8+40+6+40+6+40+6+40+6, p)){
			printf("space");
			return ' ';
		}
		//space 3
		if (keyboard_helper(4+53*4+50*2, 239+8+40+6+40+6+40+6+40+6, p)){
			printf("space");
			return ' ';
		}
		//space 4
		if (keyboard_helper(4+53*4+50*3, 239+8+40+6+40+6+40+6+40+6, p)){
			printf("space");
			return ' ';
		}
		//space 5
		if (keyboard_helper(4+53*4+50*4, 239+8+40+6+40+6+40+6+40+6, p)){
			printf("space");
			return ' ';
		}
		//space 6
		if (keyboard_helper(4+53*4+50*5, 239+8+40+6+40+6+40+6+40+6, p)){
			printf("space");
			return ' ';
		}
		if (keyboard_helper(4+53*5+50*5, 239+8+40+6+40+6+40+6+40+6, p)){
			printf("^");
			return '^';
		}
		if (keyboard_helper(4+53*6+50*5, 239+8+40+6+40+6+40+6+40+6, p)){
			printf("&");
			return '&';
		}
		if (keyboard_helper(4+53*7+50*5, 239+8+40+6+40+6+40+6+40+6, p)){
			printf("*");
			return '*';
		}
		if (keyboard_helper(4+53*8+50*5, 239+8+40+6+40+6+40+6+40+6, p)){
			printf("(");
			return '(';
		}
		if (keyboard_helper(4+53*9+50*5, 239+8+40+6+40+6+40+6+40+6, p)){
			printf(")");
			return ')';
		}


		if(p.x < 239){
			break;
		}
	}
	return '0';
}