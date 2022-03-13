#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "Touchscreen.c"

#define HW_REGS_BASE 							( 0xff200000 )
#define HW_REGS_SPAN 							( 0x00200000 )
#define HW_REGS_MASK 							( HW_REGS_SPAN - 1 )
#define	BLACK			0
#define	WHITE			1
#define	RED			2
#define	LIME			3
#define	BLUE			4
#define	YELLOW			5
#define	CYAN			6
#define	MAGENTA			7

typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef long LONG;

#pragma pack(push, 1)

typedef struct tagBITMAPFILEHEADER
{
    WORD bfType;  //specifies the file type
    DWORD bfSize;  //specifies the size in bytes of the bitmap file
    WORD bfReserved1;  //reserved; must be 0
    WORD bfReserved2;  //reserved; must be 0
    DWORD bfOffBits;  //species the offset in bytes from the bitmapfileheader to the bitmap bits
}BITMAPFILEHEADER;

#pragma pack(pop)

#pragma pack(push, 1)

typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;  //specifies the number of bytes required by the struct
    LONG biWidth;  //specifies width in pixels
    LONG biHeight;  //species height in pixels
    WORD biPlanes; //specifies the number of color planes, must be 1
    WORD biBitCount; //specifies the number of bit per pixel
    DWORD biCompression;//spcifies the type of compression
    DWORD biSizeImage;  //size of image in bytes
    LONG biXPelsPerMeter;  //number of pixels per meter in x axis
    LONG biYPelsPerMeter;  //number of pixels per meter in y axis
    DWORD biClrUsed;  //number of colors used by th ebitmap
    DWORD biClrImportant;  //number of colors that are important
}BITMAPINFOHEADER;

#pragma pack(pop)

// Contains the RGB code for the 8 colours we used for our GUI
const unsigned int OriginalColourPaletteData[8] = {
		0x00000000, // Black
		0x00FFFFFF, // White
		0x00FF0000, // Red
		0x0000FF00, // Green/Lime
		0x000000FF, // Blue
		0x00FFFF00, // Yellow
		0x0000FFFF, // Cyan
		0x00FF00FF  // Magenta
};
// graphics register addresses
#define GraphicsCommandRegOffset   				(0x00010000)
#define GraphicsStatusRegOffset   				(0x00010000)
#define GraphicsX1RegOffset						(0x00010002)
#define GraphicsY1RegOffset   					(0x00010004)
#define GraphicsX2RegOffset   					(0x00010006)
#define GraphicsY2RegOffset   					(0x00010008)
#define GraphicsColourRegOffset   				(0x0001000E)
#define GraphicsBackGroundColourRegOffset   	(0x00010010)

#define DrawHLine		1
#define DrawVLine		2
#define DrawLine		3
#define DrawCircle		0x11
#define	PutAPixel		0xA
#define	GetAPixel		0xB
#define	ProgramPaletteColour    0x10

void * virtual_base = NULL;

volatile unsigned short int *GraphicsCommandReg = NULL;
volatile unsigned short int *GraphicsStatusReg = NULL;
volatile unsigned short int *GraphicsX1Reg = NULL;
volatile unsigned short int *GraphicsY1Reg = NULL;
volatile unsigned short int *GraphicsX2Reg = NULL;
volatile unsigned short int *GraphicsY2Reg = NULL;
volatile unsigned short int *GraphicsColourReg = NULL;
volatile unsigned short int *GraphicsBackGroundColourReg = NULL;
void load_original_colour_palette(void);
void wait_for_graphics() {
	while ((*GraphicsStatusReg & 0x0001) != 0x0001);
}

int init_graphics() {
	GraphicsCommandReg = (unsigned short int *) (virtual_base
			+ (( GraphicsCommandRegOffset) & (HW_REGS_MASK)));
	if (GraphicsCommandReg == NULL) {
		printf(
				"ERROR, GraphicsCommandReg was not correctly defined. Try again");
		return 0;
	}

	GraphicsStatusReg = (unsigned short int *) (virtual_base
			+ (( GraphicsStatusRegOffset) & (HW_REGS_MASK)));
	if (GraphicsStatusReg == NULL) {
		printf("ERROR, GraphicsStatusReg was not correctly defined. Try again");
		return 0;
	}

	GraphicsX1Reg = (unsigned short int *) (virtual_base
			+ (( GraphicsX1RegOffset) & (HW_REGS_MASK)));
	if (GraphicsX1Reg == NULL) {
		printf("ERROR, GraphicsX1Reg was not correctly defined. Try again");
		return 0;
	}

	GraphicsY1Reg = (unsigned short int *) (virtual_base
			+ (( GraphicsY1RegOffset) & (HW_REGS_MASK)));
	if (GraphicsY1Reg == NULL) {
		printf("ERROR, GraphicsY1Reg was not correctly defined. Try again");
		return 0;
	}

	GraphicsX2Reg = (unsigned short int *) (virtual_base
			+ (( GraphicsX2RegOffset) & (HW_REGS_MASK)));
	if (GraphicsX2Reg == NULL) {
		printf("ERROR, GraphicsX2Reg was not correctly defined. Try again");
		return 0;
	}

	GraphicsY2Reg = (unsigned short int *) (virtual_base
			+ (( GraphicsY2RegOffset) & (HW_REGS_MASK)));
	if (GraphicsY2Reg == NULL) {
		printf("ERROR, GraphicsY2Reg was not correctly defined. Try again");
		return 0;
	}

	GraphicsColourReg = (unsigned short int *) (virtual_base
			+ (( GraphicsColourRegOffset) & (HW_REGS_MASK)));
	if (GraphicsColourReg == NULL) {
		printf("ERROR, GraphicsY2Reg was not correctly defined. Try again");
		return 0;
	}

	GraphicsBackGroundColourReg = (unsigned short int *) (virtual_base
			+ (( GraphicsBackGroundColourRegOffset) & (HW_REGS_MASK)));
	if (GraphicsBackGroundColourReg == NULL) {
		printf(
				"ERROR, GraphicsBackGroundColourReg was not correctly defined. Try again");
		return 0;
	}

	// Program the palette for the GUI
	load_original_colour_palette();

	return 1;
}

void write_pixel(int x, int y, int Colour) {
	wait_for_graphics();

	*GraphicsX1Reg = x;				// write coords to x1, y1
	*GraphicsY1Reg = y;
	*GraphicsColourReg = Colour;			// set pixel colour
	*GraphicsCommandReg = PutAPixel;	// give graphics "write pixel" command
}

void program_palette(int PaletteNumber, int RGB) {
	wait_for_graphics();

	*GraphicsColourReg = PaletteNumber;
	*GraphicsX1Reg = RGB >> 16;       // program red value in ls.8 bit of X1 reg
	*GraphicsY1Reg = RGB;      // program LIME and blue into ls 16 bit of Y1 reg
	*GraphicsCommandReg = ProgramPaletteColour; // issue command
}

void load_original_colour_palette() {
	int c = 0;
	for(c = 0; c < 8; c++) { // 8 = number of colours
		program_palette(c, OriginalColourPaletteData[c]);
	}
}

int main(int argc, char **argv)
{

	int fd;

	// Open memory as if it were a device for read and write access
	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return( 1 );
	}

	// map 2Mbyte of memory starting at 0xFF200000 to user space
	virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ),
	MAP_SHARED, fd, HW_REGS_BASE );

	if( virtual_base == MAP_FAILED ) {
		printf( "ERROR: mmap() failed...\n" );
		close( fd );
		return(1);
	}

    printf("Initializing graphics... \n");
	if(!init_graphics()) {
        printf("Failed to initialize graphics... \n");
		return 0;
	}
    printf("Done \n");


    printf("Initializing touch screen... \n");
	if(!Init_Touch()) {
        printf("Failed to initialize touch screen... \n");
		return 0;
	}
    printf("Done \n");

    while(1) {
        Point p = GetPress();
        write_pixel(p.x, p.y, 5);
    }

	return 0;
}
