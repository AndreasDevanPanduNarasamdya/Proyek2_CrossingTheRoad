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


int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crossing Highway Grid");
    InitAudioDevice();
    SetTargetFPS(60);

    float volume = 1.0f;
    // Pastikan fullscreen aktif jika dipilih dari Options
    if (isFullscreen) {
        ToggleFullscreen();
    }

    while (!WindowShouldClose()) {
        MenuOption selectedMenu = ShowMenu();

        if (selectedMenu == MENU_EXIT) {
            CloseAudioDevice();
            CloseWindow();
            return 0;
        }

        // Masuk ke Options
        if (selectedMenu == MENU_OPTIONS) {
            ShowOptions(&volume, &isFullscreen);
            continue; // Kembali ke menu utama setelah keluar dari Options
        }

        if (selectedMenu == MENU_START) {
            // *Hanya memulai game jika "Start Game" dipilih*
            InitGame();
            LoadAllTextures();
            
            Camera2D camera = {0};
            camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
            camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
            camera.rotation = 0.0f;
            camera.zoom = 1.7f;

            while (!WindowShouldClose()) {
                if (!kalah && !PermainanBerakhir) {
                    camera.target.y -= CAMERA_SPEED;
                    if (player.y * CELL_SIZE > camera.target.y + CAMERA_DEATH_DISTANCE) {
                        kalah = true;
                    }
                }   
            
                // **Pause Menu Handling**
                if (IsKeyPressed(KEY_SPACE)) {
                    isPaused = !isPaused; // Toggle Pause
                    DrawGame(camera);
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

                UpdateGame(&camera);
                // **Kamera hanya bergerak ke atas & tetap di tengah horizontal**
                DrawGame(camera);
            }

            UnloadAllTextures();
        }
        CloseAudioDevice();
        CloseWindow();
        return 0;
    }

}