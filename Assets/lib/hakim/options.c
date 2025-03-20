#include "raylib.h"
#include <stdio.h>  // Untuk printf debugging

// Fungsi untuk menampilkan menu Options
void ShowOptions(float *volume, bool *isFullscreen)
{
    int selectedOption = 0;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Options", SCREEN_WIDTH / 2 - MeasureText("Options", 30) / 2, 50, 30, DARKGRAY);
        DrawText(TextFormat("Volume: %d%%", (int)(*volume * 100)), 100, 120, 20, selectedOption == 0 ? RED : BLACK);
        DrawText(TextFormat("Fullscreen: %s", *isFullscreen ? "ON" : "OFF"), 100, 150, 20, selectedOption == 1 ? RED : BLACK);
        DrawText("Back", 100, 180, 20, selectedOption == 2 ? RED : BLACK);

        EndDrawing();

        if (IsKeyPressed(KEY_DOWN))
            selectedOption = (selectedOption + 1) % 3;
        if (IsKeyPressed(KEY_UP))
            selectedOption = (selectedOption - 1 + 3) % 3;
        if (IsKeyPressed(KEY_ENTER))
        {
            if (selectedOption == 0)
            { // Volume (belum diimplementasikan)
            }
            else if (selectedOption == 1)
            { // Fullscreen Toggle
                *isFullscreen = !(*isFullscreen);
                ToggleFullscreen();
            }
            else if (selectedOption == 2)
            { // Back
                return;
            }
        }
    }
}
