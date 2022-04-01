#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../vga/vga_lib/GraphicsRoutines.c"
#include "../wifi/wifi.c"
#include "pngutil/png.c"

#include "home.c"
#include "login.c"
#include "game.c"
#include "friendAdd.c"
#include "chat.c"
#include "sleep.c"

void gui_init()
{
    // TODO 1: Fetch backgrund colour from backend
    int background_colour = BLUE_VIOLET;
    clear_screen();
    char UID[10];
    int User_Colour = loginScreen (UID, background_colour);
    text_box_filled("Logging in...",267, 160, 300, 240, 267, 160, WHITE, GRAY);
    // Post user to our backend
    char User_Colour_String[10];
    sprintf(User_Colour_String, "%d", User_Colour);
    char post_user_args[64];
    strcpy(post_user_args, "\"");
    strcat(post_user_args, UID);
    strcat(post_user_args, "\", \"");
    strcat(post_user_args, User_Colour_String);
    strcat(post_user_args, "\"");
    api_request("post_user", post_user_args); //Send UID to backend
    // TODO 2: Fetch temperature data from backend
    char temperature[4] = "24C"; 
    while (1) {
        char* selectedFriendUID;
        char newFriendUID[10];
        int nextScreenCode;
        
        nextScreenCode = homeScreen(UID, User_Colour, selectedFriendUID, background_colour, temperature);
        // TODO 3: Send selectedFriendUID to backend
        selectedFriendUID = "friend"; //For test only
        // TODO 4: Fetch friend's colour from backend
        int Friend_Colour = ORANGE; // For test only
        if (nextScreenCode == 0) {
            // TODO 5: Update online status of the user to offline
            return;
        } else if (nextScreenCode == 1) {
            // Add friends screen
            friendAddScreen(newFriendUID, background_colour);
            // TODO 6: Send newFriendUID to backend
        } else if (nextScreenCode == 2) {
            // Chat screen
            // TODO 7: Send chat msg in chatScreen
            chatScreen (UID, selectedFriendUID, background_colour);
        } else {
            // Play screen
            // TODO 8: Fetch User score
            gameScreen (UID, selectedFriendUID, User_Colour, Friend_Colour, background_colour);
            // TODO 9: Add user score based on the game
        }
    }
}

int main(void)
{
    /* io init */
    io_bridge_init();
    init_graphics();
    Init_Touch();
    init_wifi();
    /* System Loop */
    while(1) {
        //TODO 10: check if motiondetection work
        //sleepScreen();
        gui_init();
    }
    return 0;
}