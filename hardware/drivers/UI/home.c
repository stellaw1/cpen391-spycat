#include "UI.h"

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
int homeScreen (char *UID, int userPetColour, char *selectedFriendUID) {
    //Background set the colour LIGHT_SALMON.
    box_filled(0, 0, 800, 480, LIGHT_SALMON);
    /* Draw Pets*/
    drawPNGonScreen("data.png", 50, 100, userPetColour, 300, 300);
    /* Draw return button */
    text_box_filled("< Logout", 20, 20, 30, 35, 135, 50, WHITE, GRAY);
    /* Draw friends list */
    box_filled(400, 20, 330, 350, GRAY);
    GraphicsString("Online:", 405, 25, WHITE, GRAY);
    GraphicsString("Offline:", 405, 200, WHITE, GRAY);
    /* Draw refresh button */
    drawPNGonScreen("refresh.png", 680, 340, userPetColour, 30, 24);
    /* Draw selection button chat playdate delete*/
    text_box_filled("Chat",     400, 400, 420, 405, 100, 30, WHITE, GRAY);
    text_box_filled("Playdate", 505, 400, 515, 405, 130, 30, WHITE, GRAY);
    text_box_filled("Delete",   640, 400, 650, 405, 100, 30, WHITE, GRAY);
    /* Draw add friend button*/
    text_box_filled("Add", 295, 400, 320, 405, 100, 30, WHITE, GRAY);
    
    Point p;
    while (1) {
        p = GetRelease();
        // Logout button
        if(p.x >= 20 && p.x <= 20 + 50 && p.y >= 20 && p.y <= 20 + 130){
            return 0;
		}
        // Add friend button
        if(p.x >= 400 && p.x <= 400 + 30 && p.y >= 295 && p.y <= 295 + 100){
            return 1;
		}
        // Chat button
        if(p.x >= 400 && p.x <= 400 + 30 && p.y >= 400 && p.y <= 400 + 100){
            return 2;
		}
        // Play game button
        if(p.x >= 400 && p.x <= 400 + 30 && p.y >= 505 && p.y <= 505 + 130){
            return 3;
		}
        if(p.x >= 400 && p.x <= 400 + 30 && p.y >= 640 && p.y <= 640 + 100) {
            // Delete Friend
        }
        if(p.x >= 340 && p.x <= 340 + 24 && p.y >= 340 && p.y <= 340 + 24) {
            // refresh friend list
        }
    }
} 
