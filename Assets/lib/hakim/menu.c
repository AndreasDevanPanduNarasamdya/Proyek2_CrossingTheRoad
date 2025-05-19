#include "../header.h"
MenuOption ShowMenu() {
    int selectedOption = 0;                                     
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    const char *menuOptions[] = {"Start Game", "Options", "Exit"};  
    int totalOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);

    
    if (!IsMusicStreamPlaying(menuBacksound) && isInMainMenu) {     
        PlayMenuBacksound();
    }    

    while (!WindowShouldClose()) {
        UpdateMusicStream(menuBacksound); 

        BeginDrawing();
        ClearBackground(RAYWHITE);                                  
         int titleWidth = MeasureText("Crossing The Road", 40);
        DrawText("Crossing The Road", (screenWidth - titleWidth) / 2, screenHeight / 4, 40, DARKGRAY);  


        
        for (int i = 0; i < totalOptions; i++) {
            int textWidth = MeasureText(menuOptions[i], 30);
            int posX = (GetScreenWidth() - textWidth) / 2;
            int posY = (GetScreenHeight() / 2) + i * 50;

            Color textColor = (i == selectedOption) ? WHITE : BLACK;        

            if (i == selectedOption) {
                DrawRectangle(posX - 10, posY - 5, textWidth + 20, 40, RED);
            }

            DrawText(menuOptions[i], posX, posY, 30, textColor);
        }

        EndDrawing();   

        
        if (IsKeyPressed(KEY_DOWN)) {
            selectedOption = (selectedOption + 1) % totalOptions;               
            menusound(); 
        }
        if (IsKeyPressed(KEY_UP)) {
            selectedOption = (selectedOption - 1 + totalOptions) % totalOptions; 
            menusound(); 
        }
        if (IsKeyPressed(KEY_ENTER)) {
            if (selectedOption == 1) { 
                isInMainMenu = true; 
                return MENU_OPTIONS;    
            }
            return (MenuOption)selectedOption;
        }
    }

    return MENU_EXIT;
}