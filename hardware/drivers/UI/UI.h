/*
 * https://www.figma.com/file/ZdCiLWykcCrhgA24e6RiLz/Untitled?node-id=0%3A1
 */
int loginScreen (char *UID);
void friendAddScreen (char *friendUID);
int gameScreen (char *UID, char *friendUID, int userPetColour, int friendUIColour);
void sleepScreen (void);
void chatScreen (char *UID, char *friendUID, char *rcvMsg, char *sentMsg);
void homeScreen (char *UID, int userPetColour);