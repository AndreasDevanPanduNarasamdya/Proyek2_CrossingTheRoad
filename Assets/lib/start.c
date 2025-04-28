#include "header.h"

void start() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crossing Highway Grid");
    InitAudioDevice();

    // Muat semua suara dan musik
    LoadAllSounds();

    // Mainkan backsound menu
    PlayMenuBacksound();

    SetTargetFPS(60);

    float volume = 1.0f;
    bool isFullscreen = false;

    while (!WindowShouldClose()) {
        UpdateMusicStream(menuBacksound); // Update musik backsound setiap frame

        MenuOption selectedMenu = ShowMenu();

        if (selectedMenu == MENU_EXIT) {
            StopMenuBacksound();
            UnloadAllSounds();
            CloseAudioDevice();
            CloseWindow();
            return;
        }

        if (selectedMenu == MENU_OPTIONS) {
            ShowOptions(&volume, &isFullscreen);
            continue;
        }

        if (selectedMenu == MENU_START) {
            // Hentikan suara menu saat game dimulai
            StopMenuBacksound();
            InitGame();
            LoadAllTextures();

            Camera2D camera = {0};
            camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
            camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
            camera.rotation = 0.0f;
            camera.zoom = 1.7f;

            while (!WindowShouldClose()) {
                UpdateMusicStream(backgroundMusic1); // Update musik backsound setiap frame

                if (!kalah && !PermainanBerakhir && !isPaused && gameStarted) {
                    camera.target.y -= CAMERA_SPEED;
                    if (player.y * CELL_SIZE > camera.target.y + CAMERA_DEATH_DISTANCE) {
                        kalah = true;
                    }
                }

                if (kalah || PermainanBerakhir) {
                    HandleGameOver(&kalah, &PermainanBerakhir, &camera);
                }

                if (IsKeyPressed(KEY_SPACE)) {
                    isPaused = !isPaused;
                }

                if (isPaused) {
                    // Hentikan suara menu saat game di-pause
                    StopMenuBacksound();
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
                        break;
                    }

                    continue;
                }

                UpdateGame(&camera);
                DrawGame(camera);
            }

            UnloadAllTextures();
        }
    }

    StopMenuBacksound();
    UnloadAllSounds();
    CloseAudioDevice();
    CloseWindow();
}

