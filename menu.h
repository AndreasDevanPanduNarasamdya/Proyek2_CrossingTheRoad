#ifndef MENU_H
#define MENU_H

#include "raylib.h"

typedef enum {
    MENU_START,
    MENU_OPTIONS,
    MENU_EXIT
} MenuOption;

// Fungsi untuk menampilkan menu utama
MenuOption ShowMenu();

#endif
