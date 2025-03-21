#include "menu.h"

#include <stdio.h>

MenuOption ShowMenu() {
    int selectedOption = 0;
    const char *menuOptions[] = {"Start Game", "Options", "Exit"};
    int totalOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Play the menu background music
    PlayMenuBacksound();

    while (!WindowShouldClose()) {
        // Update the music stream to ensure seamless playback
        UpdateMusicStream(menuSound);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw title
        int titleWidth = MeasureText("Crossing The Road", 40);
        DrawText("Crossing The Road", (screenWidth - titleWidth) / 2, screenHeight / 4, 40, DARKGRAY);

        // Draw menu options
        for (int i = 0; i < totalOptions; i++) {
            int textWidth = MeasureText(menuOptions[i], 30);
            int posX = (screenWidth - textWidth) / 2;
            int posY = (screenHeight / 2) + i * 50;

            Color textColor = (i == selectedOption) ? WHITE : BLACK;

            // Highlight selected option
            if (i == selectedOption) {
                DrawRectangle(posX - 10, posY - 5, textWidth + 20, 40, RED);
            }

            DrawText(menuOptions[i], posX, posY, 30, textColor);
        }

        EndDrawing();

        // Handle input
        if (IsKeyPressed(KEY_DOWN)) {
            selectedOption = (selectedOption + 1) % totalOptions;  // Move selection down
            PlayMoveChar(); // Play sound effect for navigation
        }
        if (IsKeyPressed(KEY_UP)) {
            selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;  // Move selection up
            PlayMoveChar(); // Play sound effect for navigation
        }
        if (IsKeyPressed(KEY_ENTER)) {
            PlayGetCheckpoint(); // Play sound effect for selection
            return (MenuOption)selectedOption;
        }
    }

    return MENU_EXIT;
}
