#include "../../vga/vga_lib/GraphicsRoutines.c"
  
//NOTE: (20, 0) is top left, (799, 479) is bottom right
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * do required initalization before running the app
 */
int sys_init()
{
    io_bridge_init();
    init_graphics();
    clear_screen();
    WriteAPixel(255, 255, RED);
    WriteAPixel(255, 256, YELLOW);
    WriteAPixel(255, 257, BLUE);
    WriteAPixel(255, 258, GREEN);

    OutGraphicsCharFont1(10, 10, WHITE, RED, 'A', 1);
    OutGraphicsCharFont2(100,100, WHITE, RED, 'B', 1);
    printf("Finish vga Setup");
}

int main(void)
{
    sys_init();
    return 0;
}

