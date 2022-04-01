#ifndef API_H_ /* Include Guard */
#define API_H_

#define MAX_ARG_CHARS (100)
#define MAX_RETURN_CHARS (100)
#define MAX_INPUT_CHARS (10)

int getUser(char *, char *);
int postUser(char *, int);
int incrementFriendship(char *);
int getChat(char *, char *, char *);
int postChat(char *, char *, char *);
int getFriends(char *, char *);
int postFriendship(char *, char *);
int deleteFriendship(char *, char *);
int getGame(char *, char *, char *);
int postGame(char *, char *, int);
int deleteGame(char *, char *);
#endif