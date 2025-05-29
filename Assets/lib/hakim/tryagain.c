#include "../header.h"
#define TRYAGAIN_C

void ShowTryAgain(bool *restartGame) {
    int selectedOption = 0;
    const char *options[] = {"Try Again", "Main Menu"};
    int totalOptions = 2;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Game Over", SCREEN_WIDTH / 2 - MeasureText("Game Over", 40) / 2, SCREEN_HEIGHT / 4, 40, RED);

        for (int i = 0; i < totalOptions; i++) {
            int textWidth = MeasureText(options[i], 30);
            int posX = (SCREEN_WIDTH - textWidth) / 2;
            int posY = (SCREEN_HEIGHT / 2) + i * 50;

            Color textColor = (i == selectedOption) ? WHITE : BLACK;

            if (i == selectedOption) {
                DrawRectangle(posX - 10, posY - 5, textWidth + 20, 40, RED);
            }

            DrawText(options[i], posX, posY, 30, textColor);
        }

        EndDrawing();

        if (IsKeyPressed(KEY_DOWN)) selectedOption = (selectedOption + 1) % totalOptions;
        if (IsKeyPressed(KEY_UP)) selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;
        if (IsKeyPressed(KEY_ENTER)) {
            if (selectedOption == 0) {  // Try Again
                *restartGame = true;
                return;
            } else if (selectedOption == 1) {  // Main Menu
                *restartGame = false;
                return;
            }
        }
    }
}

// modul yang menangani gameover untuk try again
void HandleGameOver(bool *kalah, bool *PermainanBerakhir, Camera2D *camera, Checkpoint *Home, HealthHP *Health, PointsXP *Points, EggyPoints *Egg) {
    printf("HandleGameOver() DIPANGGIL! Game Over terjadi!\n");

    bool restartGame = false;
    ShowTryAgain(&restartGame);
    
    if (restartGame) {

        // reset semua variabel sebelum initgame
        *kalah = false;
        *PermainanBerakhir = false;
        player.lives = MAX_LIVES;

        printf("Sebelum InitGame(): kalah = %d, PermainanBerakhir = %d, lives = %d\n", 
               *kalah, *PermainanBerakhir, player.lives);

        InitGame(Home, Health, Points, Egg); // ke initgame

        // mengembalikan kamera ke posisi semula
        camera->target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
        camera->offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        camera->rotation = 0.0f;
        camera->zoom = 1.7f;

        printf("Setelah InitGame(): kalah = %d, PermainanBerakhir = %d, lives = %d\n", 
               *kalah, *PermainanBerakhir, player.lives);

        return;
    } else {
        printf("Pemain memilih 'Main Menu'. Kembali ke menu utama.\n");
        isInMainMenu = true; // kembali ke menu utama
        *kalah = false;
        *PermainanBerakhir = false;
    }
}
