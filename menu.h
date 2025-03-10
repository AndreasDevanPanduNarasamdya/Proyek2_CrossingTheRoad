#ifndef MENU_H
#define MENU_H

#include "raylib.h"

typedef enum {
    MENU_START,
    MENU_CONTINUE,
    MENU_OPTIONS,
    MENU_EXIT
} MenuOption;

MenuOption ShowMenu();

#endif