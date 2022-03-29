#include "UI.h"
#include "../vga/vga_lib/GraphicsRoutines.c"
#include "pngutil/png.c"

/*
 * Desciption: The main menu session screen.
 *
 * @pram:      string: UID, UID is set to less than 10 characters
 * @ret:       void
 */
void homeScreen (char *UID, int userPetColour) {
    //Background set the colour LIGHT_SALMON.
    box_filled(0, 0, 800, 480, LIGHT_SALMON);
    /* Draw Pets*/
    drawPNGonScreen("data.png", 50, 100, userPetColour, 300, 300);
    /* Draw return button */
    text_box_filled("< Logout", 20, 20, 30, 35, 135, 50, WHITE, GRAY);
    /* Draw friends list */
    box_filled(400, 20, 330, 350, GRAY);
    /* Draw refresh button */
    drawPNGonScreen("refresh.png", 680, 340, userPetColour, 30, 24);
    /* Draw selection button chat playdate delete*/
    text_box_filled("Chat",     400, 400, 410, 405, 100, 30, WHITE, GRAY);
    text_box_filled("Playdate", 505, 400, 515, 405, 130, 30, WHITE, GRAY);
    text_box_filled("Delete",   640, 400, 650, 405, 100, 30, WHITE, GRAY);
    /* Draw add friend button*/
    text_box_filled("Add New Friend",   640, 400, 650, 405, 100, 30, WHITE, GRAY);
    Point p;
    while (1) {
        p = GetRelease();
        if(p.x >= 20 && p.x <= 20 + 50 && p.y >= 20 && p.y <= 20 + 90){
			printf ("TODO: Go to the login page \n");
            //TODO:
            break;
		}  
        if(!ScreenTouched())
        {
            
        }
    }
} 
