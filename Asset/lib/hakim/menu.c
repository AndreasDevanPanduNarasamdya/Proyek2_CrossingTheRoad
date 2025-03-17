#include "menu.h"
#include <stdio.h>



MenuOption ShowMenu() {
    int selectedOption = 0;
    const char *menuOptions[] = {"Start Game", "Options", "Exit"};
    int totalOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);



    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Main Menu", 320, 100, 40, DARKGRAY);

        for (int i = 0; i < totalOptions; i++) {
            Color textColor = (i == selectedOption) ? WHITE : BLACK;

            if (i == selectedOption) {
                DrawRectangle(340, 200 + i * 50, 160, 40, RED);
            }

            DrawText(menuOptions[i], 350, 210 + i * 50, 30, textColor);
        }

        EndDrawing();

        if (IsKeyPressed(KEY_DOWN)) {

            selectedOption = (selectedOption + 1) % totalOptions;
        }
        if (IsKeyPressed(KEY_UP)) {

            selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            if (selectedOption == MENU_EXIT) {

          // Clean up sound resources
                CloseWindow();
           

            }
            return (MenuOption)selectedOption;
        }
    }



    return MENU_EXIT;
}

