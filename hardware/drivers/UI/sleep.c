#include "UI.h"

/**
 * Desciption: The sleep session screen
 */
void sleepScreen (void) {
    //Background set the colour LIGHT_SALMON.
    box_filled(0, 0, 800, 480, BLACK);
    drawPNGonScreen("/img/cat_sleep.png", 250, 100, GRAY, 300, 300);
} 
