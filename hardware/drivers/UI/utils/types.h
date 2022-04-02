/*
 * Types.h
 *
 */

#include "../api/api.h"

#ifndef TYPES_H_
#define TYPES_H_

typedef enum {
    ROCK,
    PAPER,
    SCISSORS
} Choice;

typedef struct User {
    char username[MAX_INPUT_CHARS];
    char pet_colour[MAX_INPUT_CHARS];
} User;

#endif /* TYPES_H_ */