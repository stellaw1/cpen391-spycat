#include "UI.h"
#include "../vga/vga_lib/GraphicsRoutines.c"

/*
 * Desciption: The Adding friend screen
 *             User enter the fromd user name.
 *             UID will be sent back to the main function through parameter.
 *
 * @pram:      string: UID, UID is set to less than 10 characters
 * @ret:       void
 */
void friendAddScreen (char *friendUID) {
    //Background set the colour LIGHT_SALMON.
    char out[65536];
    box_filled(0, 0, 800, 480, LIGHT_SALMON);
    GraphicsString("Friend Name:", 150, 100, WHITE, LIGHT_SALMON);
    text_box_filled("", 350, 93, 360, 101, 200, 30, WHITE, GRAY);
    text_box_filled("< Home", 20, 20, 30, 35, 120, 50, WHITE, GRAY);
    TSKeyboard(out);
    int j;
    for (j = 0; j < 10; j++) {
        friendUID[j] = out[j];
    }
    text_box_filled(friendUID, 350, 93, 360, 101, 200, 30, WHITE, GRAY);
    text_box_filled("ADD", 600, 80, 630, 103, 90, 60, WHITE, GRAY);

    //Home button
    
    Point p;
    while (1) {
        p = GetRelease();
        if(p.x >= 80 && p.x <= 80 + 60 && p.y >= 600 && p.y <= 600 + 90){
			printf ("TODO: Go to the next page \n Friend added is %s \n", friendUID);
            //TODO: Check if the user name is valid or not.
            //If the user name is invalid, Input again
            break;
		}
        if(p.x >= 20 && p.x <= 20 + 50 && p.y >= 20 && p.y <= 20 + 90){
			printf ("TODO: Go to the Home page \n");
            //TODO:
            break;
		}        
    }
}