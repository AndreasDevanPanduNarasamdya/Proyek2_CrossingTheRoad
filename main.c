#include "Assets/lib/raylib.h"
#include "Assets/lib/GLOBALHEADER.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
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
    passed = false;
    DefineArrayCord();
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crossing Highway Grid");
    SetTargetFPS(60);


   float volume = 1.0f;   // Volume awal 100%
    bool isFullscreen = false;  // Default mode windowed

    while (!WindowShouldClose()) {
        MenuOption selectedMenu = ShowMenu();

        if (selectedMenu == MENU_EXIT) {
            CloseWindow();
            return 0;
        }
        
        // *Tambahkan pemanggilan menu Options*
        if (selectedMenu == MENU_OPTIONS) {
            ShowOptions(&volume, &isFullscreen);
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

    return 0;
}