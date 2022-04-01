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
    //Wi-Fi init should go here
    clear_screen();
    char UID[10];
    int User_Colour = loginScreen (UID);

    // Post user to our backend
    char User_Colour_String[10];
    sprintf(User_Colour_String, "%d", User_Colour);
    char post_user_args[64];
    strcpy(post_user_args, "\"");
    strcat(post_user_args, UID);
    strcat(post_user_args, "\", \"");
    strcat(post_user_args, User_Colour_String);
    strcat(post_user_args, "\"");
    api_request("post_user", post_user_args);

    while (1) {
        char* selectedFriendUID;
        char newFriendUID[10];
        int nextScreenCode;
        nextScreenCode = homeScreen(UID, User_Colour, selectedFriendUID);
        selectedFriendUID = "friend"; //For test only
        int Friend_Colour = ORANGE; // For test only
        if (nextScreenCode == 0) {
            // logout
            return;
        } else if (nextScreenCode == 1) {
            // Add friends screen
            friendAddScreen(newFriendUID);
        } else if (nextScreenCode == 2) {
            // Chat screen
            chatScreen (UID, selectedFriendUID);
        } else {
            // Play screen
            gameScreen (UID, selectedFriendUID, User_Colour, Friend_Colour);
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
        //check if motiondetection work
        //sleepScreen();
        gui_init();
    }
    return 0;
}