#include "raylib.h"

void ShowMenu() {
    InitWindow(800, 600, "Main Menu");
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Main Menu", 350, 250, 20, BLACK);
        EndDrawing();
    }
    
    CloseWindow();
}
