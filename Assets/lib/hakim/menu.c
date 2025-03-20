#include "menu.h"
#include <stdio.h>

MenuOption ShowMenu()
{
    int selectedOption = 0;
    const char *menuOptions[] = {"Start Game", "Options", "Exit"};
    int totalOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);

    // **Dapatkan ukuran layar**
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // **Judul Game di Tengah**
        int titleWidth = MeasureText("Crossing The Road", 40);
        DrawText("Crossing The Road", (screenWidth - titleWidth) / 2, screenHeight / 4, 40, DARKGRAY);

        for (int i = 0; i < totalOptions; i++)
        {
            int textWidth = MeasureText(menuOptions[i], 30);
            int posX = (screenWidth - textWidth) / 2;
            int posY = (screenHeight / 2) + i * 50;

            Color textColor = (i == selectedOption) ? WHITE : BLACK;

            // **Kotak highlight di belakang opsi yang dipilih**
            if (i == selectedOption)
            {
                DrawRectangle(posX - 10, posY - 5, textWidth + 20, 40, RED);
            }

            DrawText(menuOptions[i], posX, posY, 30, textColor);
        }

        EndDrawing();

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
            if (selectedOption == MENU_EXIT)
            {
                CloseWindow();
            }
            return (MenuOption)selectedOption;
        }
    }

    return MENU_EXIT;
}
