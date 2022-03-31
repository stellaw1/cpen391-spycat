#include "../../UI/friendAdd.c"
#include "../vga/vga_lib/GraphicsRoutines.c"
#include "pngutil/png.c"
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
    char out[65536];
    friendAddScreen (out);
    printf("%s", out);
}

int main(void)
{
    sys_init();
    return 0;
}