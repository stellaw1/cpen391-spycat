#include "../../UI/game.c"
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
    char *string1, *string2;
    string1 = "myname";
    string2 = "friendname";
    int result = gameScreen (string1, string2, WHITE, YELLOW);
    if (result == 0) {
        printf(" Friend wins\n");
    } else {
        printf("You wins");
    }
}

int main(void)
{
    sys_init();
    return 0;
}