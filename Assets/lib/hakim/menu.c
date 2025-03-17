#include "menu.h"
#include "../abass/sound.h"
#include "../abass/sound.c"
#include <stdio.h>

MenuOption ShowMenu()
{
    int selectedOption = 0;
    const char *menuOptions[] = {"Start Game", "Options", "Exit"};
    int totalOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);

    InitSounds(); // Initialize sounds
    PlayMenuBacksound(); // Start playing menu background music

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Display Title
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
        int titleWidth = MeasureText("Crossing The Road", 40);
        DrawText("Crossing The Road", (screenWidth - titleWidth) / 2, screenHeight / 4, 40, DARKGRAY);

        // Display Menu Options
        for (int i = 0; i < totalOptions; i++)
        {
            int textWidth = MeasureText(menuOptions[i], 30);
            int posX = (screenWidth - textWidth) / 2;
            int posY = (screenHeight / 2) + i * 50;

            Color textColor = (i == selectedOption) ? WHITE : BLACK;

            // Highlight selected option
            if (i == selectedOption)
            {
                DrawRectangle(posX - 10, posY - 5, textWidth + 20, 40, RED);
            }

            DrawText(menuOptions[i], posX, posY, 30, textColor);
        }

        EndDrawing();

        // Update the menu music
        PlayMenuBacksound();

        // Handle key inputs for navigation
        if (IsKeyPressed(KEY_DOWN))
        {
            selectedOption = (selectedOption + 1) % totalOptions;
        }
        if (IsKeyPressed(KEY_UP))
        {
            selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            StopMenuBacksound(); // Stop the menu background music
            UnloadMenuBacksound(); // Cleanup menu sound resources
            return (MenuOption)selectedOption;
        }
    }

    StopMenuBacksound(); // Stop menu background music
    UnloadMenuBacksound(); // Cleanup sound resources
    return MENU_EXIT;
}
