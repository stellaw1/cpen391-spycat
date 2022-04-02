#include "UI.h"
#include <stdio.h>


/*
 * Desciption: The game session screen.
 *             Gamers can select paper, scissors and stons to play
 *             with their partners.
 * @pram:      string: UID, UID is set to less than 10 characters
 * @ret:       void
 */
int gameScreen(char *UID, char *friendUID, char * userPetColour, int friendPetColour, int background_colour)
{
    // Background set the colour LIGHT_SALMON.
    box_filled(0, 0, 800, 480, background_colour);
    /* Draw Pets*/
    // Your pet
    drawPNGonScreen("data.png", 50, 100, atoi(userPetColour), 300, 300);
    // Your friend's pet
    drawPNGonScreen("data.png", 450, 100, friendPetColour, 300, 300);
    /* Draw return button */
    text_box_filled("< Home", 20, 20, 30, 35, 120, 50, WHITE, GRAY);
    /* Draw game choices buttons */
    text_box_filled("Rock", 200, 420, 230, 435, 120, 50, WHITE, GRAY);
    text_box_filled("Paper", 330, 420, 355, 435, 120, 50, WHITE, GRAY);
    text_box_filled("Scissors", 460, 420, 462, 435, 120, 50, WHITE, GRAY);
    /* Draw user name */
    GraphicsString(UID, 130, 390, WHITE, background_colour);
    GraphicsString(friendUID, 530, 390, WHITE, background_colour);
    box_filled(610, 420, 50, 50, GRAY);
    drawPNGonScreen("refresh.png", 620, 430, WHITE, 30, 24);
    Point p;
    while (1)
    {
        p = GetRelease();
        if (p.x >= 20 && p.x <= 20 + 50 && p.y >= 20 && p.y <= 20 + 90)
        {
            // Home button
            return 1; // TODO
        }
        if (p.x >= 420 && p.x <= 420 + 50 && p.y >= 200 && p.y <= 200 + 120)
        {
            // Rock button
            printf("Rock triggered");
            postGame(UID, friendUID, ROCK);
        }
        if (p.x >= 420 && p.x <= 420 + 50 && p.y >= 200 && p.y <= 330 + 120)
        {
            // Paper button
            printf("Paper triggered");
            postGame(UID, friendUID, PAPER);
        }
        if (p.x >= 420 && p.x <= 420 + 50 && p.y >= 460 && p.y <= 200 + 120)
        {
            // Scissors button
            printf("Scissors triggered");
            postGame(UID, friendUID, SCISSORS);
        }

        if (p.x >= 420 && p.x <= 420 + 50 && p.y >= 610 && p.y <= 610 + 50)
        {
            // Refresh button
            char ret[MAX_RETURN_CHARS];
            getGame(UID, friendUID, ret);
            // TODO: add feedback depending on ret
        }
    }
}
