#include "api.h"

/**
 * /user get request helper function
 *
 * @param username username of the user
 * @param ret return string buffer
 * @return non-negative integer on success, negative otherwise
 */
int getUser(char *username, char *ret)
{
    char args[MAX_ARG_CHARS];
    strcpy(args, "\"");
    strcat(args, username);
    strcat(args, "\"");
    return get_request("get_user", args, ret);
}

/**
 * /user post request helper function
 *
 * @param username unique ID of the user
 * @param ret return string buffer
 * @return non-negative integer on success, negative otherwise
 */
int postUser(char *username, char *pet_colour)
{
    char post_user_args[MAX_ARG_CHARS];
    strcpy(post_user_args, "\"");
    strcat(post_user_args, username);
    strcat(post_user_args, "\", \"");
    strcat(post_user_args, pet_colour);
    strcat(post_user_args, "\"");
    return api_request("post_user", post_user_args);
}

/**
 * /chat get request helper function
 *
 * @param sender sender of the chat
 * @param receiver receiver of the chat
 * @param ret return string buffer
 * @return non-negative integer on success, negative otherwise
 */
int getChat(char *sender, char *receiver, char *ret)
{
    char args[MAX_ARG_CHARS];
    strcpy(args, "\"");
    strcat(args, sender);
    strcat(args, "\", \"");
    strcat(args, receiver);
    strcat(args, "\"");
    return get_request("get_chat", args, ret);
}

/**
 * /chat post request helper function
 *
 * @param sender sender of the chat
 * @param receiver receiver of the chat
 * @param message message content of the chat
 * @return non-negative integer on success, negative otherwise
 */
int postChat(char *sender, char *receiver, char *message)
{
    char args[MAX_ARG_CHARS];
    strcpy(args, "\"");
    strcat(args, sender);
    strcat(args, "\", \"");
    strcat(args, receiver);
    strcat(args, "\", \"");
    strcat(args, message);
    strcat(args, "\"");
    return api_request("post_chat", args);
}

/**
 * /friendship get request helper function
 *
 * @param username username of the user to get friends
 * @param ret return string buffer
 * @return non-negative integer on success, negative otherwise
 */
int getIsFriends(char *user, char *friend)
{
    char args[MAX_ARG_CHARS];
    strcpy(args, "\"");
    strcat(args, user);
    strcat(args, "\", \"");
    strcat(args, friend);
    strcat(args, "\"");
    char ret[MAX_ARG_CHARS];
    get_request("get_is_friends", args, ret);
    return strlen(ret) > 2;
}

/**
 * /friendship get request helper function
 *
 * @param username username of the user to get friends
 * @param ret return string buffer
 * @return non-negative integer on success, negative otherwise
 */
int getFriends(char *username, char *ret)
{
    char args[MAX_ARG_CHARS];
    strcpy(args, "\"");
    strcat(args, username);
    strcat(args, "\"");
    return get_request("get_friends", args, ret);
}

/**
 * /friendship post request helper function
 *
 * @param username username of the user
 * @param friend friend username
 * @return non-negative integer on success, negative otherwise
 */
int postFriendship(char *user, char *friend)
{
    char args[MAX_ARG_CHARS];
    strcpy(args, "\"");
    strcat(args, user);
    strcat(args, "\", \"");
    strcat(args, friend);
    strcat(args, "\"");
    // using get here because we are checking if we add successful
    char ret[MAX_ARG_CHARS];
    get_request("post_friendship", args, ret); 
    return strlen(ret) > 2;
}

/**
 * /friendship delete request helper function
 *
 * @param username username of the user
 * @param friend friend username
 * @return non-negative integer on success, negative otherwise
 */
int deleteFriendship(char *user, char *friend)
{
    char args[MAX_ARG_CHARS];
    strcpy(args, "\"");
    strcat(args, user);
    strcat(args, "\", \"");
    strcat(args, friend);
    strcat(args, "\"");
    char ret[MAX_ARG_CHARS];
    get_request("delete_friendship", args, ret);
    return strlen(ret) > 2;
}

/**
 * /game get request helper function
 *
 * @param sender username of the sender
 * @param receiver username of the receiver
 * @param ret return string buffer
 * @return non-negative integer on success, negative otherwise
 */
int getGame(char *sender, char *receiver, char *ret)
{
    char args[MAX_ARG_CHARS];
    strcpy(args, "\"");
    strcat(args, sender);
    strcat(args, "\", \"");
    strcat(args, receiver);
    strcat(args, "\"");
    return get_request("get_game", args, ret);
}

/**
 * /game post request helper function
 *
 * @param sender username of the sender
 * @param receiver username of the receiver
 * @param choice choice of the sender
 * @return non-negative integer on success, negative otherwise
 */
int postGame(char *sender, char *receiver, char *choice)
{
    char args[MAX_ARG_CHARS]; // TODO MIGHT BE TOO SMALL
    strcpy(args, "\"");
    strcat(args, sender);
    strcat(args, "\", \"");
    strcat(args, receiver);
    strcat(args, "\", \"");
    strcat(args, choice);
    strcat(args, "\"");
    return api_request("post_game", args);
}

/**
 * /game delete request helper function
 *
 * @param sender username of the sender
 * @param receiver username of the receiver
 * @return non-negative integer on success, negative otherwise
 */
int deleteGame(char *sender, char *receiver)
{
    char args[MAX_ARG_CHARS];
    strcpy(args, "\"");
    strcat(args, sender);
    strcat(args, "\", \"");
    strcat(args, receiver);
    strcat(args, "\"");
    return api_request("delete_game", args);
}

/**
 * /weather get request helper function
 *
 * @param ret return string buffer
 * @return non-negative integer on success, negative otherwise
 */
int getWeather(char *ret)
{
    return get_request("get_weather", "", ret);
}
