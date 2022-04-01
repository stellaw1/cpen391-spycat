/*
 * https://www.figma.com/file/ZdCiLWykcCrhgA24e6RiLz/Untitled?node-id=0%3A1
 */
int loginScreen (char *UID, int background_colour);
void friendAddScreen (char *friendUID, int background_colour);
int gameScreen (char *UID, char *friendUID, int userPetColour, int friendUIColour, int background_colour);
void sleepScreen (void);
void chatScreen (char *UID, char *friendUID, int background_colour);
int homeScreen (char *UID, int userPetColour, char *selectedFriendUID, int background_colour);