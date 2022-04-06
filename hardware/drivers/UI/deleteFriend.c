#include "UI.h"

/*
 * Desciption: The search friend screen
 *             User enter the fromd user name.
 *             UID will be sent back to the main function through parameter.
 *
 * @pram:      string: UID, UID is set to less than 10 characters
 * @ret:       void
 */
void deleteFriendScreen(char *UID, char *friendUID, int background_colour)
{
    friendUID[MAX_INPUT_CHARS] = '\0';
    // Background set the colour LIGHT_SALMON.
    char out[65536];
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
        if (p.x >= 80 && p.x <= 80 + 60 && p.y >= 600 && p.y <= 600 + 130)
        {
            // check if friend exists
            char ret[MAX_RETURN_CHARS];
            if (deleteFriendship(UID, friendUID))
            {
                text_box_filled("Success", 267, 160, 300, 240, 267, 160, WHITE, GRAY);
                break;
            }
            else
            {
                GraphicsString("Not valid friend", 350, 120, WHITE, background_colour);
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