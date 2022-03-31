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
 
 OutGraphicsCharFont2(85, 100, WHITE, BLACK, 'H', 1);
 OutGraphicsCharFont2(100, 100, WHITE, BLACK, 'E', 1);
 OutGraphicsCharFont2(115, 100, WHITE, BLACK, 'L', 1);
 OutGraphicsCharFont2(130, 100, WHITE, BLACK, 'L', 1);
 OutGraphicsCharFont2(145, 100, WHITE, BLACK, 'O', 1);
 OutGraphicsCharFont2(160, 100, WHITE, BLACK, ',', 1);
 OutGraphicsCharFont2(175, 100, WHITE, BLACK, 'W', 1);
 OutGraphicsCharFont2(190, 100, WHITE, BLACK, 'O', 1);
 OutGraphicsCharFont2(205, 100, WHITE, BLACK, 'R', 1);
 OutGraphicsCharFont2(220, 100, WHITE, BLACK, 'L', 1);    
 OutGraphicsCharFont2(235, 100, WHITE, BLACK, 'D', 1);
 OutGraphicsCharFont2(250, 100, WHITE, BLACK, '!', 1);

 GraphicsString("Hello From DE1-SoC Linux", 10, 10, WHITE, BLACK);
 GraphicsString("If you see this line on screen, congratulation: TEST PASSED", 10, 25, WHITE, BLACK);
 GraphicsString("PASSED", 10, 40, RED, BLACK);
printf("Finish vga Setup");
}

int main(void)
{
    sys_init();
    return 0;
}

