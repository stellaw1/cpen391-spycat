#include "UI.h"
#include "searchFriend.c"

/*
 * Desciption: The main menu session screen.
 *
 * @pram:      string: UID, UID is set to less than 10 characters
 * @ret:       Next screen code
 *             0: login screen
 *             1: Add friends screen
 *             2: Chat screen
 *             3: Play screen
 */
int homeScreen(char *UID, char *userPetColour, char *selectedFriendUID, int background_colour)
{
    // Set Background png according to weather
    char tempinCelsius[20];
    getWeather(tempinCelsius);

    // Background set the colour LIGHT_SALMON.
    int isFriendSelected = 0;

    Point p;
    while (1)
    {
        box_filled(0, 0, 800, 480, background_colour);
        /* Draw Pets*/
        drawPNGonScreen("data.png", 50, 100, atoi(userPetColour), 300, 300);
        /* Draw return button */
        text_box_filled("< Logout", 20, 20, 30, 35, 135, 50, WHITE, GRAY);

        /* Show weather on screen */
        GraphicsString("Temperature:", 430, 200, WHITE, background_colour);
        GraphicsString(tempinCelsius, 430, 220, WHITE, background_colour);

        /* Draw selection button chat playdate delete*/
        text_box_filled("Chat", 400, 400, 420, 405, 100, 30, WHITE, GRAY);
        text_box_filled("Playdate", 505, 400, 515, 405, 130, 30, WHITE, GRAY);
        text_box_filled("Delete", 640, 400, 650, 405, 100, 30, WHITE, GRAY);
        /* Draw add friend button*/
        text_box_filled("Add", 295, 400, 320, 405, 100, 30, WHITE, GRAY);

        /* Search friend */
        text_box_filled("Search Friend", 400, 350, 450, 355, 330, 30, WHITE, GRAY);
        /* Print the selected friend name */
        if (isFriendSelected)
        {
            GraphicsString("Selected Friend:", 430, 280, WHITE, background_colour);
            GraphicsString(selectedFriendUID, 430, 300, WHITE, background_colour);
        }
        Point p;
        while (1)
        {
            p = GetRelease();
            // Logout button
            if (p.y >= 20 && p.y <= 20 + 50 && p.x >= 20 && p.x <= 20 + 130)
            {
                return 0;
            }
            // Add friend button
            if (p.y >= 400 && p.y <= 400 + 30 && p.x >= 295 && p.x <= 295 + 100)
            {
                return 1;
            }
            // Chat button
            if (p.y >= 400 && p.y <= 400 + 30 && p.x >= 400 && p.x <= 400 + 100)
            {
                if (!isFriendSelected)
                {
                    text_box_filled("No friend selected", 267, 160, 300, 240, 267, 160, WHITE, GRAY);
                    break;
                }
                else
                {
                    return 2;
                }
            }
            // Play game button
            if (p.y >= 400 && p.y <= 400 + 30 && p.x >= 505 && p.x <= 505 + 130)
            {
                if (!isFriendSelected)
                {
                    text_box_filled("No friend selected", 267, 160, 300, 240, 267, 160, WHITE, GRAY);
                    break;
                }
                else
                {
                    return 3;
                }
            }
            // Delete friend ship
            if (p.y >= 400 && p.y <= 400 + 30 && p.x >= 640 && p.x <= 640 + 100)
            {
                if (!isFriendSelected)
                {
                    text_box_filled("No friend selected", 267, 160, 300, 240, 267, 160, WHITE, GRAY);
                    break;
                }
                else
                {
                    return 4;
                }
            }
            // Search Friend
            if (p.y >= 350 && p.y <= 350 + 30 && p.x >= 400 && p.x <= 400 + 330)
            {
                searchFriendScreen(UID, selectedFriendUID, background_colour);

                isFriendSelected = 1;
                break;
            }
        }
    }
}
