#ifndef API_H_
#define API_H_

#define MAX_TEXT_CHARS (100)
#define MAX_ARG_CHARS (100)
#define MAX_RETURN_CHARS (100)
#define MAX_INPUT_CHARS (10)

int getUser(char *, char *);
int postUser(char *, char *);
int getChat(char *, char *, char *);
int postChat(char *, char *, char *);
int getFriends(char *, char *);
int postFriendship(char *, char *);
int deleteFriendship(char *, char *);
int getGame(char *, char *, char *);
int postGame(char *, char *, char *);
int deleteGame(char *, char *);
#endif