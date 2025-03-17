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

    // **Variabel untuk opsi game**
    float volume = 1.0f;   // Volume awal 100%
    bool isFullscreen = false;  // Default mode windowed

    while (!WindowShouldClose()) {
        MenuOption selectedMenu = ShowMenu();

        if (selectedMenu == MENU_EXIT) {
            CloseWindow();
            return 0;
        }
        
        // **Tambahkan pemanggilan menu Options**
        if (selectedMenu == MENU_OPTIONS) {
            ShowOptions(&volume, &isFullscreen);
        }

        if (selectedMenu == MENU_START) {
            // **Hanya memulai game jika "Start Game" dipilih**
            InitGame();
            LoadAllTextures();

            Camera2D camera = {0};
            camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
            camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
            camera.rotation = 0.0f;
            camera.zoom = 1.0f;

            while (!WindowShouldClose()) {
                UpdateGame();

                if (!kalah && !PermainanBerakhir) {
                    camera.target.y -= CAMERA_SPEED;
                    if (player.y * CELL_SIZE > camera.target.y + CAMERA_DEATH_DISTANCE) {
                        kalah = true;
                    }
                }

                DrawGame(camera);
            }

            UnloadAllTextures();
        }
    }

    CloseWindow();
    return 0;
}
