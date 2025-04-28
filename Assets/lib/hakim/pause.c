#include "pause.h"

void HandlePause(bool *isPaused, bool *isInMainMenu, float *volume, bool *isFullscreen) {
    if (IsKeyPressed(KEY_SPACE)) {
        *isPaused = !(*isPaused); 
    }

    if (*isPaused) {
        StopMusicStream(backgroundMusic1); //menghentikan musik 
        BeginDrawing();
        ClearBackground(GRAY);

        DrawText("PAUSED", GetScreenWidth() / 2 - MeasureText("PAUSED", 40) / 2, GetScreenHeight() / 2 - 50, 40, RED);
        DrawText("Press SPACE to Resume", GetScreenWidth() / 2 - MeasureText("Press SPACE to Resume", 20) / 2, GetScreenHeight() / 2, 20, BLACK);
        DrawText("Press BACKSPACE to Exit to Main Menu", GetScreenWidth() / 2 - MeasureText("Press BACKSPACE to Exit to Main Menu", 20) / 2, GetScreenHeight() / 2 + 60, 20, BLACK);

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) {
            ShowOptions(volume, isFullscreen); //pergi ke pengaturan
        }
        if (IsKeyPressed(KEY_BACKSPACE)) {
            *isInMainMenu = true; //kembali ke manu utama
            StopMusicStream(backgroundMusic1);
        }
    }
}
