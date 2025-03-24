#ifndef MENU_H
#define MENU_H


typedef enum {
    MENU_START,
    MENU_OPTIONS,
    MENU_EXIT
} MenuOption;

bool isInMainMenu = true;

MenuOption ShowMenu();

#endif
