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
    readFromFile("data.png");
    unsigned x = 0;
    unsigned y = 0;
    for (x = 0; x < 300; x++) {
        for (y = 0; y < 300; y++){
            if (rgba_data[x][y].a != 0) {
                WriteAPixel (x, y, GREEN);
            }
        }
    }
}

int main(void)
{
    sys_init();
    return 0;
}