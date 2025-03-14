#include "menu.h"
#include <stdio.h>
// #include "../fahraj/sfx.c"

MenuOption ShowMenu() {
    int selectedOption = 0;
    const char *menuOptions[] = {"Start Game", "Options", "Exit"};
    int totalOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);

    // PlayMusicStream(menuBacksound); // Play menu music

    while (!WindowShouldClose()) {
        // UpdateMusicStream(menuBacksound); // Keep menu music streaming

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
            // PlayMoveSound(); // Play navigation sound
            selectedOption = (selectedOption + 1) % totalOptions;
        }
        if (IsKeyPressed(KEY_UP)) {
            // PlayMoveSound(); // Play navigation sound
            selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;
        }
        if (IsKeyPressed(KEY_ENTER)) {
            if (selectedOption == MENU_EXIT) {
                // StopMusicStream(menuBacksound); // Stop menu music
                // UnloadSounds();                // Clean up sound resources
                CloseWindow();
            } else {
                // StopMusicStream(menuBacksound); // Stop menu music
                // PlayMusicStream(backgroundMusic); // Start game music
            }
            return (MenuOption)selectedOption;
        }
    }

    // StopMusicStream(menuBacksound);
    // UnloadSounds();
    return MENU_EXIT;
}

