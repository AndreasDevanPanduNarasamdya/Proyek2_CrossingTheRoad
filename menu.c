#include "menu.h"
#include <stdio.h>

MenuOption ShowMenu() {
    int selectedOption = 0;
    const char *menuOptions[] = {"Start Game", "Continue", "Options", "Exit"};
    int totalOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Main Menu", 320, 100, 40, DARKGRAY);
        for (int i = 0; i < totalOptions; i++) {
            Color color = (i == selectedOption) ? RED : BLACK;
            DrawText(menuOptions[i], 350, 200 + i * 50, 30, color);
        }

        EndDrawing();

        if (IsKeyPressed(KEY_DOWN)) {
            selectedOption = (selectedOption + 1) % totalOptions;
        }
        if (IsKeyPressed(KEY_UP)) {
            selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            return (MenuOption)selectedOption;
        }
    }
    return MENU_EXIT;
}
