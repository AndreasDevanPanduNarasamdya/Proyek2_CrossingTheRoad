#include "menu.h"
#include "../fahraj/sfx.h"
#include "../fahraj/sfx.c"
#include <stdio.h>

MenuOption ShowMenu()
{
    int selectedOption = 0;
    const char *menuOptions[] = {"Start Game", "Options", "Exit"};
    int totalOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);

    // Initialize sounds and play menu music
    InitSounds();
    PlayMenuBacksound(); // Start playing the menu background music (set to loop)

    while (!WindowShouldClose())
    {
        // Keep updating the music stream to loop seamlessly
        UpdateMusicStream(menuSound);

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

            // Highlight the selected option
            if (i == selectedOption)
            {
                DrawRectangle(posX - 10, posY - 5, textWidth + 20, 40, RED);
            }

            DrawText(menuOptions[i], posX, posY, 30, textColor);
        }

        EndDrawing();

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
            // Stop and clean up music resources when exiting the menu
            StopMusicStream(menuSound); // Stop the menu music
            UnloadSounds();             // Unload all sound resources
            return (MenuOption)selectedOption;
        }
    }

    // Stop and clean up music resources on exit
    StopMusicStream(menuSound);
    UnloadSounds();
    return MENU_EXIT;
}
