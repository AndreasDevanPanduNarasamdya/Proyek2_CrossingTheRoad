#include "header.h"

void start() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crossing Highway Grid");
    InitAudioDevice();

    LoadAllSounds();
    PlayMenuBacksound();
    SetTargetFPS(60);

    float volume = 1.0f;
    bool isFullscreen = false;

    while (!WindowShouldClose()) {
        if (isInMainMenu) {  
            UpdateMusicStream(menuBacksound);
    
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
                isInMainMenu = false;
                StopMenuBacksound();
                InitGame();
                LoadAllTextures();
            }
        }
    
        Camera2D camera = {0};
        camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
        camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        camera.rotation = 0.0f;
        camera.zoom = 1.7f;
    
        while (!WindowShouldClose() && !isInMainMenu) {
            UpdateMusicStream(backgroundMusic1);
    
            if (!kalah && !PermainanBerakhir && !isPaused && gameStarted) {
                camera.target.y -= CAMERA_SPEED;
                if (player.y * CELL_SIZE > camera.target.y + CAMERA_DEATH_DISTANCE) {
                    kalah = true;
                }
            }
    
            if (kalah || PermainanBerakhir) {
                HandleGameOver(&kalah, &PermainanBerakhir, &camera);
    
                if (isInMainMenu) {
                    UnloadAllTextures();
                    StopMusicStream(backgroundMusic1);
                    break;  
                } else {
                    InitGame(); 
                    continue;
                }
            }
    
            if (IsKeyPressed(KEY_SPACE)) {
                isPaused = !isPaused;
            }
    
            if (isPaused) {
                HandlePause(&isPaused, &isInMainMenu, &volume, &isFullscreen);
    
                if (isInMainMenu) {
                    UnloadAllTextures();
                    StopMusicStream(backgroundMusic1);
                    break; 
                }
                continue;
            }
    
            UpdateGame(&camera);
            DrawGame(camera);
        }

        UnloadAllTextures();
    }
    

    StopMenuBacksound();
    UnloadAllSounds();
    CloseAudioDevice();
    CloseWindow();
}

