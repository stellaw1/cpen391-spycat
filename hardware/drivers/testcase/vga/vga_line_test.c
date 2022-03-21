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
horizontal_line(10, 10, 200, GREEN);

vertical_line(10, 10, 200, GREEN);

line(10, 10, 200, 50, GREEN);
printf("Finish vga Setup");
}

int main(void)
{
    sys_init();
    return 0;
}