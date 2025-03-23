#include "../header.h"

void ShowOptions(float *volume, bool *isFullscreen) {
    int selectedOption = 0;

    while (!WindowShouldClose()) {
        UpdateMusicStream(menuBacksound); 

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Options", SCREEN_WIDTH / 2 - MeasureText("Options", 30) / 2, 50, 30, DARKGRAY);
        DrawText(TextFormat("Volume: %d%%", (int)(*volume * 100)), 100, 120, 20, selectedOption == 0 ? RED : BLACK);
        DrawText(TextFormat("Fullscreen: %s", *isFullscreen ? "ON" : "OFF"), 100, 150, 20, selectedOption == 1 ? RED : BLACK);
        DrawText("Back", 100, 180, 20, selectedOption == 2 ? RED : BLACK);

        EndDrawing();

        // Navigasi
        if (IsKeyPressed(KEY_DOWN)) selectedOption = (selectedOption + 1) % 3;
        if (IsKeyPressed(KEY_UP)) selectedOption = (selectedOption - 1 + 3) % 3;

        // Perubahan volume
        if (selectedOption == 0) {
            if (IsKeyDown(KEY_LEFT) && *volume > 0.0f) {
                *volume -= 0.01f; // mwngurangi volume
                if (*volume < 0.0f) *volume = 0.0f;
            }
            if (IsKeyDown(KEY_RIGHT) && *volume < 1.0f) {
                *volume += 0.01f; // menambah volume
                if (*volume > 1.0f) *volume = 1.0f;
            }
            SetMasterVolume(*volume); // menyimpan perubahan volume
        }

        
        if (IsKeyPressed(KEY_ENTER)) {
            if (selectedOption == 1) { // untuk fullscreen
                *isFullscreen = !(*isFullscreen);
                ToggleFullscreen();
            } else if (selectedOption == 2) { // opsi 2 untuk kembali ke menu utama
                return;
            }
        }
    }
}
