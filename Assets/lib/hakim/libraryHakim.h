#ifndef LIBRARY_HAKIM_H
#define LIBRARY_HAKIM_H

#include <stdbool.h>
#include "../header.h"

/// ====== menu.h ======
typedef enum {              
    MENU_START,
    MENU_OPTIONS,
    MENU_EXIT
} MenuOption;

bool isInMainMenu = true;

    MenuOption ShowMenu(); 


/// ====== options.h ======
void ShowOptions(float *volume, bool *isFullscreen);

/// ====== pause.h ======
void HandlePause(bool *isPaused, bool *isInMainMenu, float *volume, bool *isFullscreen);

/// ====== tryagain.h ======
void ShowTryAgain(bool *restartGame);
void HandleGameOver(bool *kalah, bool *PermainanBerakhir, Camera2D *camera, Checkpoint *Home, HealthHP *Health, PointsXP *Points, EggyPoints *Egg);

#endif // LIBRARY_HAKIM_H
