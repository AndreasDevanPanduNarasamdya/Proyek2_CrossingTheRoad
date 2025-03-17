#include "Assets/lib/raylib.h"
#include "Assets/lib/GLOBALHEADER.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Assets/lib/andreas/HeaderAndrew.h"
#include "Assets/lib/andreas/LibraryAndrew.c"
#include "Assets/lib/faiz/LibraryFaiz.h"
#include "Assets/lib/faiz/LibraryFaiz.c"
#include "Assets/lib/azzam/LibraryAzzam.h"
#include "Assets/lib/azzam/LibraryAzzam.c"
#include "Assets/lib/hakim/menu.h"
#include "Assets/lib/hakim/menu.c"
#include "Assets/lib/hakim/options.h"
#include "Assets/lib/hakim/options.c"

// Variabel global untuk game
bool isPaused = false; // Apakah game sedang pause
float volume = 1.0f;   // Volume awal
bool isFullscreen = false; // Fullscreen mode awal

void DrawGame(Camera2D camera) {
    BeginDrawing();
    ClearBackground(WHITE);

    BeginMode2D(camera);

    sprintf(coordText, "X: %d, Y: %d", player.x, player.y);

    RenderGrid();
    RenderRoads(SCREEN_WIDTH, SCREEN_HEIGHT);
    RenderCars(&numCars, cars);
    RenderCharacter(&PlayerSprite, player);

    EndMode2D();

    RenderInstructions(player, coordText, level);

    if (PermainanBerakhir) {
        DrawText("MENANG", player.x * CELL_SIZE, player.y * CELL_SIZE, 40, RED);
    }

    if (kalah) {
        DrawText("GAME OVER", player.x * CELL_SIZE, player.y * CELL_SIZE, 40, RED);
        PermainanBerakhir = true;
    }

    EndDrawing();
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crossing Highway Grid");
    SetTargetFPS(60);

    // Pastikan fullscreen aktif jika dipilih dari Options
    if (isFullscreen) {
        ToggleFullscreen();
    }

    while (!WindowShouldClose()) {
        MenuOption selectedMenu = ShowMenu();

        if (selectedMenu == MENU_EXIT) {
            CloseWindow();
            return 0;
        }

        // Masuk ke Options
        if (selectedMenu == MENU_OPTIONS) {
            ShowOptions(&volume, &isFullscreen);
            continue; // Kembali ke menu utama setelah keluar dari Options
        }

        // Memulai game
        InitGame();
        LoadAllTextures();

        camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
        camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;

        while (!WindowShouldClose()) {
            // **Pause Menu Handling**
            if (IsKeyPressed(KEY_SPACE)) {
                isPaused = !isPaused; // Toggle Pause
            }

            if (isPaused) {
                BeginDrawing();
                ClearBackground(GRAY);

                DrawText("PAUSED", SCREEN_WIDTH / 2 - MeasureText("PAUSED", 40) / 2, SCREEN_HEIGHT / 2 - 50, 40, RED);
                DrawText("Press SPACE to Resume", SCREEN_WIDTH / 2 - MeasureText("Press SPACE to Resume", 20) / 2, SCREEN_HEIGHT / 2, 20, BLACK);
                DrawText("Press ENTER for Options", SCREEN_WIDTH / 2 - MeasureText("Press ENTER for Options", 20) / 2, SCREEN_HEIGHT / 2 + 30, 20, BLACK);
                DrawText("Press ESC to Exit to Main Menu", SCREEN_WIDTH / 2 - MeasureText("Press ESC to Exit to Main Menu", 20) / 2, SCREEN_HEIGHT / 2 + 60, 20, BLACK);

                EndDrawing();

                if (IsKeyPressed(KEY_ENTER)) {
                    ShowOptions(&volume, &isFullscreen);
                }
                if (IsKeyPressed(KEY_ESCAPE)) {
                    break; // Kembali ke Main Menu
                }

                continue; // Jangan jalankan UpdateGame() saat pause
            }

            UpdateGame();
            DrawGame(camera);
        }

        UnloadAllTextures();
    }

    CloseWindow();
    return 0;
}