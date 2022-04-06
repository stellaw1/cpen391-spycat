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
    memset(rcvMsg, '\0', sizeof(rcvMsg));
    getChat(friendUID, UID, rcvMsg);
    char sentMsg[MAX_TEXT_CHARS];
    char out[MAX_TEXT_CHARS];
    rcvMsg[0] = '\0';
    sentMsg[0] = '\0';
    out[0] = '\0';
    // Background set the colour LIGHT_SALMON.
    box_filled(0, 0, 800, 480, background_colour);
    /* Draw Home button */
    text_box_filled("< Home", 20, 20, 30, 35, 120, 50, WHITE, GRAY);
    // send button
    text_box_filled("Send", 20, 120, 30, 135, 120, 50, WHITE, GRAY);
    /* Chat Box */
    drawPNGonScreen("chat.png", 200, 20, GRAY, 600, 200);
    /* textbox friend*/
    text_box_filled(rcvMsg, 200 + 85, 20 + 25, 200 + 85, 20 + 25, 420, 30, WHITE, GRAY);
    /* textbox user*/

    /* Touch Keyboard*/
    TSKeyboard(out, 10);
    int j = 0;
    while (j < 10)
    {
        sentMsg[j] = out[j];
        j++;
        if (out[j] == '\0')
        {
            break;
        }
    }
    sentMsg[j] = '\0';

    Point p;
    while (1)
    {
        p = GetRelease();

        // home button
        if (p.x >= 20 && p.x <= 20 + 50 && p.y >= 20 && p.y <= 20 + 90)
        {
            return;
        }

        // refresh button
        if (p.x >= 20 && p.x <= 20 + 30 && p.y >= 750 && p.y <= 750 + 24)
        {
            drawPNGonScreen("chat.png", 200, 20, GRAY, 600, 200);
            getChat(UID, friendUID, rcvMsg);
            text_box_filled(rcvMsg, 200 + 85, 20 + 25, 200 + 85, 20 + 25, 420, 30, WHITE, GRAY);
        }

        // send button
        if (p.x >= 120 && p.x <= 120 + 50 && p.y >= 20 && p.y <= 20 + 120)
        {
            postChat(UID, friendUID, sentMsg);
            drawPNGonScreen("chat.png", 200, 20, GRAY, 600, 200);
            text_box_filled(rcvMsg, 200 + 85, 20 + 25, 200 + 85, 20 + 25, 420, 30, WHITE, GRAY);
            sentMsg[j] = '\0';
            text_box_filled(sentMsg, 200 + 110, 20 + 110, 200 + 110, 20 + 110, 420, 30, WHITE, GRAY);
        }
    }
}
