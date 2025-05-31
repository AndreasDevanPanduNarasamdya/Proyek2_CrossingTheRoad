#include "../header.h"

static Rectangle buttonBounds[3]; // jumlah tombol

static bool DrawButton(const char *text, int posX, int posY, int fontSize, bool selected, int index, float globalAlpha) {
    int textWidth = MeasureText(text, fontSize);
    int buttonWidth = textWidth + 60;
    int buttonHeight = fontSize + 20;
    
    buttonBounds[index] = (Rectangle){ (float)posX - buttonWidth/2, (float)posY - buttonHeight/2, (float)buttonWidth, (float)buttonHeight };
    
    Color buttonColor = selected ? GAME_YELLOW : GAME_BLUE;
    Color textColor = selected ? GAME_DARK : GAME_LIGHT;

    // Terapkan globalAlpha pada warna tombol
    DrawRectangleRec(buttonBounds[index], ColorAlpha(buttonColor, globalAlpha));
    DrawRectangleLinesEx(buttonBounds[index], 1, ColorAlpha(GAME_DARK, globalAlpha)); // Ketebalan garis bisa disesuaikan
    
    if (selected) {
        DrawRectangle(buttonBounds[index].x + 3, buttonBounds[index].y + 3, buttonBounds[index].width, buttonBounds[index].height, ColorAlpha(GAME_DARK, 0.3f * globalAlpha));
    }
    
    DrawText(text, posX - textWidth/2, posY - fontSize/2, fontSize, ColorAlpha(textColor, globalAlpha));
    
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, buttonBounds[index]);
}



MenuOption ShowMenu() {
    int selectedOption = 0;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    const char *menuOptions[] = {"Start Game", "Options", "Exit"};
    int totalOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);

    // Inisialisasi elemen UI
    InitUIElements(screenWidth, screenHeight);

    // Inisialisasi buttonBounds
    for (int i = 0; i < totalOptions; i++) {
        buttonBounds[i] = (Rectangle){ 0, 0, 0, 0 }; // Akan diupdate oleh DrawButton
    }
    

    if (!IsMusicStreamPlaying(menuBacksound) && isInMainMenu) { 
        PlayMenuBacksound();
    }

    while (!WindowShouldClose()) {
        // Perbarui animasi UI 
        UpdateUIElements(screenWidth, screenHeight);
        
        // Dapatkan alpha global saat ini untuk digunakan pada tombol
        float currentGlobalAlpha = GetUIGlobalAlpha();

        // Mouse handling untuk tombol
        Vector2 mousePos = GetMousePosition();

        for (int i = 0; i < totalOptions; i++) {
            if (CheckCollisionPointRec(mousePos, buttonBounds[i])) { // Cek dengan bounds dari frame sebelumnya
                if (selectedOption != i) {
                    selectedOption = i;
                }
                
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    switch (selectedOption) {
                        case 0: return MENU_START; // Asumsi MENU_START_GAME = 0
                        case 1: return MENU_OPTIONS;    // Asumsi MENU_OPTIONS = 1
                        case 2: return MENU_EXIT;       // Asumsi MENU_EXIT = 2
                        default: break; 
                    }
                }
            }
        }
        
        // Update music stream
        UpdateMusicStream(menuBacksound); 

        BeginDrawing();
            // Draw background
            DrawBackground(screenWidth, screenHeight);
            
            // Draw animated car
            DrawPixelCar(carPosition.x, carPosition.y, 1.5f, GAME_RED);
            
            // Draw player character on right side
            DrawPixelChicken(screenWidth - 120, screenHeight - 170, 2.0f, WHITE);
            
            // Draw title with bounce effect
            const char* title = "Why Did the Chicken Cross The Road?";
            int titleFontSize = 35;
            int titleWidth = MeasureText(title, titleFontSize);
            
            // Title shadow
            DrawText(title, (screenWidth - titleWidth)/2 + 4, screenHeight/4 - 50 + 4, 
                    titleFontSize, ColorAlpha(GAME_DARK, 0.5f * globalAlpha));
                    
            // Title with bounce effect
            DrawText(title, (screenWidth - titleWidth)/2, screenHeight/4 - 50 + sin(frameCounter/10.0f) * 5.0f, 
                    titleFontSize, ColorAlpha(GAME_YELLOW, globalAlpha));
            
            // Subtitle
            const char* subtitle = "A Crossy Road Inspired Game";
            int subtitleFontSize = 20;
            int subtitleWidth = MeasureText(subtitle, subtitleFontSize);
            DrawText(subtitle, (screenWidth - subtitleWidth)/2, 
                    screenHeight/4 + 10 + sin(frameCounter/10.0f) * 5.0f, 
                    subtitleFontSize, ColorAlpha(GAME_LIGHT, globalAlpha));
            
            // Menu Options (Buttons)
            for (int i = 0; i < totalOptions; i++) {
                float buttonY = (screenHeight/2 + 50) + i * 70;
                
                bool isHovered = DrawButton(
                    menuOptions[i], 
                    screenWidth/2, 
                    buttonY, 
                    30, 
                    i == selectedOption,
                    i,
                    currentGlobalAlpha // Teruskan alpha global untuk konsistensi
                );

            }
            
            DrawCopyright(screenWidth, screenHeight);
            
        EndDrawing();
        
        // Keyboard navigation
        if (IsKeyPressed(KEY_DOWN)) {
            selectedOption = (selectedOption + 1) % totalOptions;
            menusound(); 
        }
        if (IsKeyPressed(KEY_UP)) {
            selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;
            menusound();
        }
        if (IsKeyPressed(KEY_ENTER)) {
            menusound();

            switch (selectedOption) {
                case 0: return MENU_START;
                case 1: return MENU_OPTIONS;
                case 2: return MENU_EXIT;
                default: break;
            }
        }
    }
    return MENU_EXIT;
}