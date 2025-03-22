#include "../header.h"

void start() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crossing Highway Grid");
    SetTargetFPS(60);
    float volume = 1.0f;
    if (isFullscreen) {
        ToggleFullscreen();
    }
    while (!WindowShouldClose()) {
        MenuOption selectedMenu = ShowMenu();

        if (selectedMenu == MENU_EXIT) {

            CloseWindow();
            return; // Exit the game
        }

        if (selectedMenu == MENU_OPTIONS) {
            ShowOptions(&volume, &isFullscreen);
            continue; // Return to main menu after options
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
                if (!kalah && !PermainanBerakhir) {
                    camera.target.y -= CAMERA_SPEED;
                    if (player.y * CELL_SIZE > camera.target.y + CAMERA_DEATH_DISTANCE) {
                        kalah = true;
                    }
                }

                if (kalah || PermainanBerakhir) {
                    HandleGameOver(&kalah, &PermainanBerakhir);
                }

                if (IsKeyPressed(KEY_SPACE)) {
                    isPaused = !isPaused; // Toggle pause
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
                        break;
                    }

                    continue; // Skip UpdateGame() when paused
                }

                UpdateGame(&camera);
                DrawGame(camera);
            }

            UnloadAllTextures();
        }
    }
    CloseAudioDevice();    }
