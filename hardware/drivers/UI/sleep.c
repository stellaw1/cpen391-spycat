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
    // Your pet
    drawPNGonScreen("data.png", 250, 100, GRAY, 300, 300);
    // // Your friend's pet
    // Point p;
    // while (1) {
    //     p = GetRelease();
    //     if(p.x >= 0 && p.x <= 479 && p.y >= 0 && p.y <= 799){
    //         break;
	// 	}
    // }
} 
