#include "UI.h"

/**
 * Desciption: The search friend screen
 *             User enter the fromd user name.
 *             UID will be sent back to the main function through parameter.
 *
 * @pram:      string: UID, UID is set to less than 10 characters
 */
void searchFriendScreen(char *UID, char *friendUID, int background_colour)
{
    friendUID[MAX_INPUT_CHARS] = '\0';
    // Background set the colour LIGHT_SALMON.
    char out[MAX_INPUT_CHARS];
    memset(out, '\0', sizeof(out));
    box_filled(0, 0, 800, 480, background_colour);
    GraphicsString("Friend Name:", 150, 100, WHITE, background_colour);
    text_box_filled("", 350, 93, 360, 101, 200, 30, WHITE, GRAY);
    TSKeyboard(out, 10);
    strcpy(friendUID, out);
    text_box_filled(out, 350, 93, 360, 101, 200, 30, WHITE, GRAY);
    text_box_filled("Search", 600, 80, 630, 103, 130, 60, WHITE, GRAY);
    // Home button
    Point p;
    while (1)
    {
        p = GetRelease();
        if (p.x >= 80 && p.x <= 80 + 60 && p.y >= 600 && p.y <= 600 + 130)
        {
            // check if friend exists
            text_box_filled("Searching...", 267, 160, 300, 240, 267, 160, WHITE, GRAY);
            if (getIsFriends(UID, friendUID))
            {
                text_box_filled("Success", 267, 160, 300, 240, 267, 160, WHITE, GRAY);
                break;
            }
            else
            {
                text_box_filled("Cannot find friend", 267, 160, 300, 240, 267, 160, WHITE, GRAY);
                memset(friendUID, '\0', sizeof(friendUID));
                break;
            }
        }
        if (p.x >= 20 && p.x <= 20 + 50 && p.y >= 20 && p.y <= 20 + 90)
        {
            // return to home screen
            return;
        }
    }
}