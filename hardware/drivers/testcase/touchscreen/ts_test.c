
  
//NOTE: (20, 0) is top left, (799, 479) is bottom right
#include <stdio.h>

#include "../../io_bridge.h"
#include "../../touchscreen/Touchscreen.h"
/**
 * do required initalization before running the app
 */
int sys_init()
{
    io_bridge_init();
    Init_Touch();
    Point p;
    while (1){
        p = GetPress();
        printf("x=%d, y=%d\n",p.x, p.y);
    }
    printf("Finish touch Setup");

}

int main(void)
{
    sys_init();
    return 0;
}
