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

// **Tambahkan fungsi ini agar main.c bisa lebih bersih**
void HandleGameOver(bool *kalah, bool *PermainanBerakhir, Camera2D *camera) {
    printf("HandleGameOver() DIPANGGIL! Game Over terjadi!\n");

    bool restartGame = false;
    ShowTryAgain(&restartGame);
    
    if (restartGame) {
        printf("Pemain memilih 'Try Again'. Reset game...\n");

        // **Reset semua variabel sebelum InitGame**
        *kalah = false;
        *PermainanBerakhir = false;
          // Reset nyawa sebelum InitGame()

        printf("Sebelum InitGame(): kalah = %d, PermainanBerakhir = %d, lives = %d\n", 
               *kalah, *PermainanBerakhir, player.lives);

        InitGame(); // **Reset game**

        camera->target.y = player.y * CELL_SIZE; // reset kamera

        printf("Setelah InitGame(): kalah = %d, PermainanBerakhir = %d, lives = %d\n", 
               *kalah, *PermainanBerakhir, player.lives);

        return;
    } else {
        printf("Pemain memilih 'Main Menu'. Keluar dari game.\n");
        CloseAudioDevice();
        CloseWindow();
        exit(0);
    }
}
