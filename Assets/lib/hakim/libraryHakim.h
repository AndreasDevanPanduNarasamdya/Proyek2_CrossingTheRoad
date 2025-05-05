#ifndef LIBRARY_HAKIM_H
#define LIBRARY_HAKIM_H

#include <stdbool.h>
#include "raylib.h"

/// ====== menu.h ======
typedef enum {              
    MENU_START,
    MENU_OPTIONS,
    MENU_EXIT
} MenuOption;

extern bool isInMainMenu;
MenuOption ShowMenu();

/// ====== options.h ======
void ShowOptions(float *volume, bool *isFullscreen);

/// ====== pause.h ======
void PauseGame();
void ResumeGame();

/// ====== tryagain.h ======
void ShowTryAgain(bool *restartGame);
void HandleGameOver(bool *kalah, bool *PermainanBerakhir, Camera2D *camera); 

#endif // LIBRARY_HAKIM_H
