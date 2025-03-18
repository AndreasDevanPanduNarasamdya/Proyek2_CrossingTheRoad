#include "menu.h"
#include "../fahraj/sfx.h"
#include <stdio.h>

MenuOption ShowMenu()
{
    int selectedOption = 0;
    const char *menuOptions[] = {"Start Game", "Options", "Exit"};
    int totalOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);

    // Inisialisasi audio dan mulai memutar musik menu
    InitSounds();
    PlayMenuBacksound(); // Mulai memutar musik menu

    while (!WindowShouldClose())
    {
        // Update musik menu melalui fungsi di sfx.h
        PlayMenuBacksound();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Tampilkan Judul
        int screenWidth = GetScreenWidth();
        int screenHeight = GetScreenHeight();
        int titleWidth = MeasureText("Crossing The Road", 40);
        DrawText("Crossing The Road", (screenWidth - titleWidth) / 2, screenHeight / 4, 40, DARKGRAY);

        // Tampilkan Opsi Menu
        for (int i = 0; i < totalOptions; i++)
        {
            int textWidth = MeasureText(menuOptions[i], 30);
            int posX = (screenWidth - textWidth) / 2;
            int posY = (screenHeight / 2) + i * 50;

            Color textColor = (i == selectedOption) ? WHITE : BLACK;

            // Sorot opsi yang dipilih
            if (i == selectedOption)
            {
                DrawRectangle(posX - 10, posY - 5, textWidth + 20, 40, RED);
            }

            DrawText(menuOptions[i], posX, posY, 30, textColor);
        }

        EndDrawing();

        // Handle input untuk navigasi menu
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
            // Hentikan musik dan bersihkan resource audio sebelum keluar dari menu
            UnloadSounds();
            return (MenuOption)selectedOption;
        }
    }

    // Hentikan musik dan bersihkan resource audio saat keluar
    UnloadSounds();
    return MENU_EXIT;
}
