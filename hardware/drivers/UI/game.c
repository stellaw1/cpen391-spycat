#include "UI.h"
#include "../vga/vga_lib/GraphicsRoutines.c"

/*
 * Desciption: The game session screen.
 *             Gamers can select paper, scissors and stons to play 
 *             with their partners.
 * @pram:      string: UID, UID is set to less than 10 characters
 * @ret:       void
 */
void gameScreen (char *UID, char *friendUID, int userPetColour, int friendUIColour) {
    //Background set the colour LIGHT_SALMON.
    box_filled(0, 0, 800, 480, LIGHT_SALMON);
    // Pet Colour
    int Colour = WHITE; //default colour is white, adjust the colour using the buttons on the left and right.
    int i = 1; // WHITE
    text_box_filled("<", 350, 150, 360, 158, 30, 30, WHITE, GRAY);
    text_box_filled(">", 470, 150, 480, 158, 30, 30, WHITE, GRAY);
    box_filled(400, 150, 50, 30, Colour);
    text_box_filled("", 350, 100, 360, 108, 200, 30, WHITE, GRAY);
    TSKeyboard(out);
    int j;
    for (j = 0; j < 10; j++) {
        UID[j] = out[j];
    }
    text_box_filled(UID, 350, 100, 360, 108, 200, 30, WHITE, GRAY);
    text_box_filled("LOGIN", 600, 125, 610, 148, 90, 60, WHITE, GRAY);
    Point p;
    while (1) {
        p = GetRelease();
        if(p.x >= 125 && p.x <= 125 + 60 && p.y >= 600 && p.y <= 600 + 90){
			printf ("TODO: Go to the next page \n Colour selected is %d \n", Colour);
            break;
		}
        if(!ScreenTouched())
        {
            // Paper Scissors, Stone gaming button function
            // if(p.x >= 150 && p.x <= 150 + 30 && p.y >= 350 && p.y <= 350 + 30){
            //     i = (i - 1 < 0) ? 0 : i - 1;
            //     Colour = ColourPalletteData[i];
            //     box_filled(400, 150, 50, 30, Colour);
            // }
        }
    }
    return Colour;
} 
