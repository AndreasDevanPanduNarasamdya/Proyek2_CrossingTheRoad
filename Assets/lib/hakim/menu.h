#ifndef MENU_H
#define MENU_H


typedef enum {              //enum untuk menyimpan nilai konstan
    MENU_START,
    MENU_OPTIONS,
    MENU_EXIT
} MenuOption;

bool isInMainMenu = true;

    MenuOption ShowMenu();  //tipe datanya adalah menuoption yang nanti hanya akan memiliki 3 jenis output

#endif
