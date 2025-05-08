#include "../header.h"

void HandlePause(bool *isPaused, bool *isInMainMenu, float *volume, bool *isFullscreen) {

    if (*isPaused) {
        StopMusicStream(backgroundMusic1);
        BeginDrawing();
        ClearBackground(GRAY);

        DrawText("PAUSED", GetScreenWidth() / 2 - MeasureText("PAUSED", 40) / 2, GetScreenHeight() / 2 - 50, 40, RED);
        DrawText("Press SPACE to Resume", GetScreenWidth() / 2 - MeasureText("Press SPACE to Resume", 20) / 2, GetScreenHeight() / 2, 20, BLACK);
        DrawText("Press ENTER for Options", GetScreenWidth() / 2 - MeasureText("Press ENTER for Options", 20) / 2, GetScreenHeight() / 2 + 30, 20, BLACK);
        DrawText("Press Q to Exit to Main Menu", GetScreenWidth() / 2 - MeasureText("Press Q to Exit to Main Menu", 20) / 2, GetScreenHeight() / 2 + 60, 20, BLACK); // 🔥 Ganti jadi Q

        EndDrawing();

        if (IsKeyPressed(KEY_ENTER)) {
            ShowOptions(volume, isFullscreen);
        }
        if (IsKeyPressed(KEY_Q)) { 
            *isInMainMenu = true;
            StopMusicStream(backgroundMusic1);
        }
    }
}
