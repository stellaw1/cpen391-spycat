/*
 * https://www.figma.com/file/ZdCiLWykcCrhgA24e6RiLz/Untitled?node-id=0%3A1
 */
int loginScreen (char *UID);
void friendAddScreen (char *friendUID);
int gameScreen (char *UID, char *friendUID, int userPetColour, int friendUIColour);
void sleepScreen (void);
void chatScreen (char *UID, char *friendUID);
int homeScreen (char *UID, int userPetColour, char *selectedFriendUID);