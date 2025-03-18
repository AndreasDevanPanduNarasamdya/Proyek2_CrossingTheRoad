#include "Assets/lib/raylib.h"
#include "Assets/lib/GLOBALHEADER.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Assets/lib/andreas/HeaderAndrew.h"
#include "Assets/lib/faiz/LibraryFaiz.h"
#include "Assets/lib/azzam/LibraryAzzam.h"
#include "Assets/lib/hakim/menu.h"
#include "Assets/lib/hakim/options.h"
#include "Assets/lib/fahraj/sfx.h" 

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crossing Highway Grid");
    InitAudioDevice();
    SetTargetFPS(60);

    InitSounds();  // Initialize all sound resources

    float volume = 1.0f;
    bool isFullscreen = false;

    if (isFullscreen) {
        ToggleFullscreen();
    }

    while (!WindowShouldClose()) {
        PlayMenuBacksound();  // Play menu background sound

        MenuOption selectedMenu = ShowMenu();

        if (selectedMenu == MENU_EXIT) {
            UnloadSounds();  // Unload all audio resources
            CloseAudioDevice();
            CloseWindow();
            return 0;
        }

        if (selectedMenu == MENU_OPTIONS) {
            ShowOptions(&volume, &isFullscreen);
            UpdateVolume(volume);  // Update sound volumes if changed
            continue;
        }

        if (selectedMenu == MENU_START) {
            InitGame();
            LoadAllTextures();

            Camera2D camera = {0};
            camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
            camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
            camera.rotation = 0.0f;
            camera.zoom = 1.7f;

            while (!WindowShouldClose()) {
                if (!isPaused) {
                    if (!kalah && !PermainanBerakhir) {
                        camera.target.y -= CAMERA_SPEED;
                        if (player.y * CELL_SIZE > camera.target.y + CAMERA_DEATH_DISTANCE) {
                            kalah = true;
                        }
                    }
                    UpdateGame(&camera);
                }

                BeginDrawing();
                ClearBackground(RAYWHITE);

                if (isPaused) {
                    DrawText("PAUSED", SCREEN_WIDTH / 2 - MeasureText("PAUSED", 40) / 2, SCREEN_HEIGHT / 2 - 50, 40, RED);
                    DrawText("Press SPACE to Resume", SCREEN_WIDTH / 2 - MeasureText("Press SPACE to Resume", 20) / 2, SCREEN_HEIGHT / 2, 20, DARKGRAY);
                    DrawText("Press ENTER for Options", SCREEN_WIDTH / 2 - MeasureText("Press ENTER for Options", 20) / 2, SCREEN_HEIGHT / 2 + 30, 20, DARKGRAY);
                    DrawText("Press ESC to Exit to Main Menu", SCREEN_WIDTH / 2 - MeasureText("Press ESC to Exit to Main Menu", 20) / 2, SCREEN_HEIGHT / 2 + 60, 20, DARKGRAY);

                    if (IsKeyPressed(KEY_SPACE)) {
                        isPaused = false;
                    } else if (IsKeyPressed(KEY_ENTER)) {
                        ShowOptions(&volume, &isFullscreen);
                        UpdateVolume(volume);
                    } else if (IsKeyPressed(KEY_ESCAPE)) {
                        break;
                    }
                } else {
                    DrawGame(camera);
                }

                EndDrawing();

                if (kalah || PermainanBerakhir) {
                    break;
                }
            }

            UnloadAllTextures();
        }
    }

    UnloadSounds();  // Unload sound resources before exiting
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
