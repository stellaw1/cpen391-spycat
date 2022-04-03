#include "UI.h"

/*
 * Desciption: The main login screen.
 *             User enter the user name, and select their pet colour.
 *             UID will be sent back to the main function through parameter.
 *
 * @pram:      string: UID, UID is set to less than 10 characters
 * @ret:       Color
 */
void chatScreen(char *UID, char *friendUID, int background_colour)
{
    char rcvMsg[MAX_TEXT_CHARS];
    getChat(UID, friendUID, rcvMsg);
    char sentMsg[MAX_TEXT_CHARS]; // For test only
    char out[MAX_TEXT_CHARS];
    // Background set the colour LIGHT_SALMON.
    box_filled(0, 0, 800, 480, background_colour);
    /* Draw return button */
    text_box_filled("< Home", 20, 20, 30, 35, 120, 50, WHITE, GRAY);
    // Pet Colour
    /* Screen title*/
    // GraphicsString("Chat", 350, 20, WHITE, LIGHT_SALMON);
    /* Chat Box */
    drawPNGonScreen("chat.png", 200, 20, GRAY, 600, 200);
    /* textbox friend*/
    text_box_filled(rcvMsg, 200 + 85, 20 + 25, 200 + 85, 20 + 25, 420, 30, WHITE, GRAY);
    /* textbox user*/

    /* Touch Keyboard*/
    TSKeyboard(sentMsg, 100);
    int j;
    for (j = 0; j < 100; j++)
    {
        sentMsg[j] = out[j];
    }
    text_box_filled(sentMsg, 200 + 110, 20 + 110, 200 + 110, 20 + 110, 420, 30, WHITE, GRAY);
    postChat(UID, friendUID, sentMsg);
    Point p;
    while (1)
    {
        p = GetRelease();
        if (p.x >= 20 && p.x <= 20 + 50 && p.y >= 20 && p.y <= 20 + 90)
        {
            return;
        }
        if (!ScreenTouched())
        {
        }
    }
}