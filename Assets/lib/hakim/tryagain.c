#include "../header.h"
#define TRYAGAIN_C

void ShowTryAgain(bool *restartGame) {
    UnloadAllSounds();
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
            if (selectedOption == 0) {  
                *restartGame = true;
                return;
            } else if (selectedOption == 1) {  
                *restartGame = false;
                return;
            }
        }
    }
}

void HandleGameOver(bool *kalah, bool *PermainanBerakhir, Camera2D *camera) {
    

    bool restartGame = false;
    ShowTryAgain(&restartGame);
    
    if (restartGame) {
        
        *kalah = false;
        *PermainanBerakhir = false;
        player.lives = MAX_LIVES; 


        InitGame(); 

        camera->target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
        camera->offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        camera->rotation = 0.0f;
        camera->zoom = 1.7f;



        return;
    } else {
        isInMainMenu = true; 
    }
}
