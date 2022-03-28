#include "../../UI/login.c"
#include "../../UI/pngutil/png.c"
  
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
    Init_Touch();
    clear_screen();
    drawPNGonScreen("test.png", 50, 50, GREEN);
}

int main(void)
{
    sys_init();
    return 0;
}