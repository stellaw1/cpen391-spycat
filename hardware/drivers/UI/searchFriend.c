#include "UI.h"

/*
 * Desciption: The search friend screen
 *             User enter the fromd user name.
 *             UID will be sent back to the main function through parameter.
 *
 * @pram:      string: UID, UID is set to less than 10 characters
 * @ret:       void
 */
void searchFriendScreen(char *UID, char *friendUID, int background_colour)
{
    friendUID[MAX_INPUT_CHARS] = '\0';
    // Background set the colour LIGHT_SALMON.
    char out[MAX_INPUT_CHARS];
    box_filled(0, 0, 800, 480, background_colour);
    GraphicsString("Friend Name:", 150, 100, WHITE, background_colour);
    text_box_filled("", 350, 93, 360, 101, 200, 30, WHITE, GRAY);
    TSKeyboard(out, 10);
    int j = 0;
    while (j < 10)
    {
        friendUID[j] = out[j];
        j++;
        if (out[j] == '\0')
        {
            break;
        }
    }
    friendUID[j] = '\0';
    text_box_filled(out, 350, 93, 360, 101, 200, 30, WHITE, GRAY);
    text_box_filled("Search", 600, 80, 630, 103, 130, 60, WHITE, GRAY);
    // Home button
    Point p;
    while (1)
    {
        p = GetRelease();
        if (p.y >= 80 && p.y <= 80 + 60 && p.x >= 600 && p.x <= 600 + 130)
        {
            // check if friend exists
            char ret[MAX_RETURN_CHARS];
            getIsFriends(UID, friendUID, ret);
            if (atoi(ret))
            {
                text_box_filled("Success", 267, 160, 300, 240, 267, 160, WHITE, GRAY);
                break;
            }
            else
            {
                GraphicsString("Not valid friend name", 350, 120, WHITE, background_colour);
                break;
            }
        }
    }
}