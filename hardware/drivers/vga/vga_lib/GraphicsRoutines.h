// #defined constants representing values we write to the graphics 'command' register to get
// it to do something. You will add more values as you add hardware to the graphics chip
// Note DrawHLine, DrawVLine and DrawLine at the moment do nothing - you will modify these


void wait_for_graphics(void);
int init_graphics(void);
void write_pixel (int x, int y, int Colour);
int read_pixel (int x, int y);
void ProgramPalette(int PaletteNumber, int RGB);
void clear_screen(void);
void OutGraphicsCharFont1(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase);
void OutGraphicsCharFont2(int x, int y, int colour, int backgroundcolour, int c, int Erase);