/*
 * https://www.figma.com/file/ZdCiLWykcCrhgA24e6RiLz/Untitled?node-id=0%3A1
 */
int loginScreen(char *UID, char *pet_colour, int background_colour);
void friendAddScreen(char *friendUID, int background_colour);
int gameScreen(char *UID, char *friendUID, char *userPetColour, int friendUIColour, int background_colour);
void sleepScreen(void);
void chatScreen(char *UID, char *friendUID, int background_colour);
int homeScreen(char *UID, char *userPetColour, char *selectedFriendUID, int background_colour, char *tempinCelsius);
void searchFriendScreen(char *UID, char *friendUID, int background_colour);
