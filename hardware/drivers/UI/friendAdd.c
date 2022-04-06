#include "UI.h"

/*
 * Desciption: The Adding friend screen
 *             User enter the fromd user name.
 *             UID will be sent back to the main function through parameter.
 *
 * @pram:      string: UID, UID is set to less than 10 characters
 * @ret:       void
 */
void friendAddScreen(char * UID, char *friendUID, int background_colour)
{
    friendUID[MAX_INPUT_CHARS] = '\0';
    // Background set the colour LIGHT_SALMON.
    char out[65536];
    box_filled(0, 0, 800, 480, background_colour);
    GraphicsString("Friend Name:", 150, 100, WHITE, background_colour);
    text_box_filled("", 350, 93, 360, 101, 200, 30, WHITE, GRAY);
    text_box_filled("< Home", 20, 20, 30, 35, 120, 50, WHITE, GRAY);
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
    text_box_filled("ADD", 600, 80, 630, 103, 90, 60, WHITE, GRAY);
    // Home button
    Point p;
    while (1)
    {
        p = GetRelease();
        if (p.y >= 80 && p.y <= 80 + 60 && p.x >= 600 && p.x <= 600 + 90)
        {
            // check if friend exists
            char ret[MAX_RETURN_CHARS];
            if (!getUser(friendUID, ret))
            {
                break;
            }

            // add friend
            postFriendship(UID, friendUID);
        }
        if (p.y >= 20 && p.y <= 20 + 50 && p.x >= 20 && p.x <= 20 + 90)
        {
            // return to home screen
            return;
        }
    }
}