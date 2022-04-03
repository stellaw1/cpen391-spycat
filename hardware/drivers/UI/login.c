#include "UI.h"

/*
 * Desciption: The main login screen.
 *             User enter the user name, and select their pet colour.
 *             UID will be sent back to the main function through parameter.
 *
 * @pram:      string: UID, UID is set to less than 10 characters
 * @ret:       Color
 */
int loginScreen(char *UID, char *pet_colour, int background_colour)
{
    // Background set the colour LIGHT_SALMON.
    box_filled(0, 0, 800, 480, background_colour);
    GraphicsString("User Name:", 150, 100, WHITE, background_colour);
    GraphicsString("Pet Colour:", 150, 150, WHITE, background_colour);
    // Pet Colour
    int Colour = ColourPalletteData[WHITE]; // default colour is white, adjust the colour using the buttons on the left and right.
    int userColour = WHITE;                 // WHITE
    text_box_filled("<", 350, 150, 360, 158, 30, 30, WHITE, GRAY);
    text_box_filled(">", 470, 150, 480, 158, 30, 30, WHITE, GRAY);
    box_filled(400, 150, 50, 30, userColour);
    text_box_filled("", 350, 100, 360, 108, 200, 30, WHITE, GRAY);

    // fill username
    TSKeyboard(UID, 10);
    text_box_filled(UID, 350, 100, 360, 108, 200, 30, WHITE, GRAY);
    text_box_filled("LOGIN", 600, 125, 610, 148, 90, 60, WHITE, GRAY);

    Point p;

    while (1)
    {
        p = GetRelease();

        // login button pressed
        if (p.x >= 125 && p.x <= 125 + 60 && p.y >= 600 && p.y <= 600 + 90)
        {
            text_box_filled("Logging in...", 267, 160, 300, 240, 267, 160, WHITE, GRAY);
            // Post user to our backend, do nothing if fail
            if (postUser(UID, userColour))
            {
                sprintf(pet_colour, "%d", userColour);
                return 1;
            }
        }

        // select colour
        if (!ScreenTouched())
        {
            if (p.x >= 150 && p.x <= 150 + 30 && p.y >= 350 && p.y <= 350 + 30)
            {
                userColour = (userColour - 1 < 0) ? 0 : userColour - 1;
                // Colour = ColourPalletteData[userColour];
                box_filled(400, 150, 50, 30, userColour);
            }
            if (p.x >= 150 && p.x <= 150 + 30 && p.y >= 470 && p.y <= 470 + 30)
            {
                userColour = (userColour + 1 > 63) ? 63 : userColour + 1;
                // Colour = ColourPalletteData[userColour];
                box_filled(400, 150, 50, 30, userColour);
            }
        }
    }

    // should never get here
    return 0;
}