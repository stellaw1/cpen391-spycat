/**
 * @file types.h
 * @author your name (you@domain.com)
 * @brief define custom types for global User variable
 */

#include "../api/api.h"

#ifndef TYPES_H_
#define TYPES_H_

typedef struct User {
    char username[MAX_INPUT_CHARS];
    char pet_colour[MAX_INPUT_CHARS];
} User;

#endif /* TYPES_H_ */