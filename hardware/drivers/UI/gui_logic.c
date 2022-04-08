#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <python3.5/Python.h>

#include "./utils/types.h"
#include "../vga/vga_lib/GraphicsRoutines.c"
#include "../wifi/wifi.c"
#include "pngutil/png.c"
#include "./api/api.c"
#include "../audio/audio.c"

#include "home.c"
#include "login.c"
#include "game.c"
#include "friendAdd.c"
#include "deleteFriend.c"
#include "chat.c"
#include "sleep.c"

struct User *USER;

void gui_init()
{
    // initialize global user
    USER = malloc(sizeof(struct User));
    memset(USER->username, '\0', sizeof(USER->username));
    memset(USER->pet_colour, '\0', sizeof(USER->pet_colour));

    // Get background colour from backend
    int background_colour = BLUE_VIOLET;
    clear_screen();
    play();
    loginScreen(USER->username, USER->pet_colour, background_colour);
    text_box_filled("Logging in...", 267, 160, 300, 240, 267, 160, WHITE, GRAY);

    while (1)
    {
        char friendUID[10];
        memset(friendUID, '\0', sizeof(friendUID));
        char colourString[10];
        int nextScreenCode;

        nextScreenCode = homeScreen(USER->username, USER->pet_colour, friendUID, background_colour);
        text_box_filled("Loading...", 267, 160, 300, 240, 267, 160, WHITE, GRAY);
        // strcpy(friendUID, "friend"); // For test only
        if (strlen(friendUID) > 0)
        {
            getUser(friendUID, colourString);
        }
        int Friend_Colour = atoi(colourString);
        if (nextScreenCode == 0)
        {
            return;
        }
        else if (nextScreenCode == 1)
        {
            // Add friends screen
            memset(friendUID, '\0', sizeof(friendUID));
            friendAddScreen(USER->username, friendUID, background_colour);
        }
        else if (nextScreenCode == 2)
        {
            // Chat screen
            chatScreen(USER->username, friendUID, background_colour);
        }
        else if (nextScreenCode == 3)
        {
            // Play screen
            gameScreen(USER->username, friendUID, USER->pet_colour, Friend_Colour, background_colour);
        }
        else if (nextScreenCode == 4)
        {
            memset(friendUID, '\0', sizeof(friendUID));
            deleteFriendScreen(USER->username, friendUID, background_colour);
        }
        else if (nextScreenCode == 5)
        {

            FILE *fp;
            Py_Initialize();
            fp = _Py_fopen("../../../software/motion-detection/python3_call.py", "r");
            sleepScreen();
            PyRun_SimpleFile(fp, "../../../software/motion-detection/python3_call.py");
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
    FILE *fp;
    Py_Initialize();
    fp = _Py_fopen("../../../software/motion-detection/python3_call.py", "r");
    while (1)
    {
        sleepScreen();
        PyRun_SimpleFile(fp, "../../../software/motion-detection/python3_call.py");
        gui_init();
    }
    Py_Finalize();
    return 0;
}
