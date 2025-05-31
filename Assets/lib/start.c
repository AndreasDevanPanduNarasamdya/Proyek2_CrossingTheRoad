#include "header.h"

void start(Checkpoint *Home, HealthHP *Health, PointsXP *Points, EggyPoints *Egg) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crossing Highway Grid");
    InitAudioDevice();

    LoadAllSounds();
    PlayMenuBacksound();
    SetTargetFPS(60);
    LoadLeaderboardFromFile("leaderboard.txt");

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
                InitGame(Home, Health, Points, Egg);
                LoadAllTextures();
            }
        }
    
        Camera2D camera = {0};
        camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
        camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        camera.rotation = 0.0f;
        camera.zoom = 1.7f;
    
        while (!WindowShouldClose() && !isInMainMenu) {
            UpdateMusicStream(backgroundMusic);
    
            if (!kalah && !PermainanBerakhir && !isPaused && gameStarted) {
                camera.target.y -= CAMERA_SPEED;
                if (player.y * CELL_SIZE > camera.target.y + CAMERA_DEATH_DISTANCE) {
                    kalah = true;
                }
                
                if (level == 11) {
                menang = true;
                PermainanBerakhir = true;
                }
            }
    
            if (kalah || PermainanBerakhir) {
                HandleGameOver(&kalah, &PermainanBerakhir, &camera, Home, Health, Points, Egg);
    
                if (isInMainMenu) {
                    UnloadAllTextures();
                    StopMusicStream(backgroundMusic);
                    break;  
                } else {
                    InitGame(Home, Health, Points, Egg); 
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
                    StopMusicStream(backgroundMusic);
                    break; 
                }
                continue;
            }

            if (menang) {
    // Panggil input username & simpan skor
                if (!usernameEntered) {
        // Gunakan fungsi InputPlayerName yang sudah ada
                char playerName[MAX_PLAYER_NAME_LENGTH];
             InputPlayerName(playerName, MAX_PLAYER_NAME_LENGTH);
        
         if (strlen(playerName) > 0) {
            SaveScoreToLeaderboard(playerName, player.score); 
        }
        usernameEntered = true;
    }

    // Gambar layar menang
         BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawSharedUILayout(SCREEN_WIDTH, SCREEN_HEIGHT, "CONGRATULATIONS!", NULL, false);
    
    // Pesan selamat
    DrawText("SELAMAT! KAMU MENANG!", 
             SCREEN_WIDTH/2 - MeasureText("SELAMAT! KAMU MENANG!", 30)/2, 
             SCREEN_HEIGHT/2 - 60, 30, GREEN);
    
    // Tampilkan skor
    char scoreText[100];
    sprintf(scoreText, "Skor Akhir: %d", player.score);
    DrawText(scoreText, 
             SCREEN_WIDTH/2 - MeasureText(scoreText, 25)/2, 
             SCREEN_HEIGHT/2 - 20, 25, DARKGREEN);
    
    // Instruksi
    DrawText("Tekan ENTER untuk kembali ke menu", 
             SCREEN_WIDTH/2 - MeasureText("Tekan ENTER untuk kembali ke menu", 20)/2, 
             SCREEN_HEIGHT/2 + 20, 20, DARKGRAY);
    
    EndDrawing();

    // Check input untuk kembali ke menu
    if (IsKeyPressed(KEY_ENTER)) {
        isInMainMenu = true;
        menang = false;
        usernameEntered = false;
        PermainanBerakhir = false;
        // Reset level jika perlu
        level = 1;
    }
}
    
            UpdateGame(&camera, Home, Health, Points, Egg);
            DrawGame(camera, Home, Health, Points, Egg);
        }

        UnloadAllTextures();
    }
    
    SaveLeaderboardToFile("leaderboard.txt");
    StopMenuBacksound();
    UnloadAllSounds();
    CloseAudioDevice();
    CloseWindow();
}

