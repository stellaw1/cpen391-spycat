#include "UI.h"

/*
 * Desciption: The main login screen.
 *             User enter the user name, and select their pet colour.
 *             UID will be sent back to the main function through parameter.
 *
 * @pram:      string: UID, UID is set to less than 10 characters
 * @ret:       Color
 */
int loginScreen (char *UID) {
    //Background set the colour LIGHT_SALMON.
    char *out = malloc(sizeof(char)*65536);
    box_filled(0, 0, 800, 480, LIGHT_SALMON);
    GraphicsString("User Name:", 150, 100, WHITE, LIGHT_SALMON);
    GraphicsString("Pet Colour:", 150, 150, WHITE, LIGHT_SALMON);
    // Pet Colour
    int Colour = WHITE; //default colour is white, adjust the colour using the buttons on the left and right.
    int i = 1; // WHITE
    text_box_filled("<", 350, 150, 360, 158, 30, 30, WHITE, GRAY);
    text_box_filled(">", 470, 150, 480, 158, 30, 30, WHITE, GRAY);
    box_filled(400, 150, 50, 30, Colour);
    text_box_filled("", 350, 100, 360, 108, 200, 30, WHITE, GRAY);
    TSKeyboard(out);
    UID = out;
    free(out);
    text_box_filled(UID, 350, 100, 360, 108, 200, 30, WHITE, GRAY);
    text_box_filled("LOGIN", 600, 125, 610, 148, 90, 60, WHITE, GRAY);
    Point p;
    while (1) {
        p = GetRelease();
        if(p.x >= 125 && p.x <= 125 + 60 && p.y >= 600 && p.y <= 600 + 90){
            break;
		}
        if(!ScreenTouched())
        {
            if(p.x >= 150 && p.x <= 150 + 30 && p.y >= 350 && p.y <= 350 + 30){
                i = (i - 1 < 0) ? 0 : i - 1;
                Colour = ColourPalletteData[i];
                box_filled(400, 150, 50, 30, Colour);
            }
            if(p.x >= 150 && p.x <= 150 + 30 && p.y >= 470 && p.y <= 470 + 30){
                i = (i + 1 > 63) ? 63 : i + 1;
                Colour = ColourPalletteData[i];
                box_filled(400, 150, 50, 30, Colour);
            }
        }
    }
    return Colour;
}