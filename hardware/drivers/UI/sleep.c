#include "UI.h"
/*
 * Desciption: The sleep session screen.
 *             
 * @pram:      void
 * @ret:       void
 */
void sleepScreen (void) {
    //Background set the colour LIGHT_SALMON.
    box_filled(0, 0, 800, 480, BLACK);
    /* Draw Pets*/
    drawPNGonScreen("data_sleep.png", 250, 100, GRAY, 300, 300);
} 
