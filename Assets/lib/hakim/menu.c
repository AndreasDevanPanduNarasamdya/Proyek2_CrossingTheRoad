#include "../header.h"

// Game theme colors
#define GAME_GREEN        (Color){ 87, 201, 111, 255 }   // Main theme green
#define GAME_BLUE         (Color){ 76, 157, 240, 255 }   // Accent blue
#define GAME_YELLOW       (Color){ 255, 207, 64, 255 }   // Bright yellow
#define GAME_RED          (Color){ 255, 97, 97, 255 }    // Bright red
#define GAME_PURPLE       (Color){ 185, 102, 235, 255 }  // Purple accent
#define GAME_DARK         (Color){ 49, 55, 65, 255 }     // Dark background color
#define GAME_LIGHT        (Color){ 245, 245, 245, 255 }  // Light text color

// Animation variables
typedef struct {
    float value;         // Current value
    float target;        // Target value
    float speed;         // Animation speed
} Animator;

// UI element variables
static Animator titleBounce = { 0.0f, 1.0f, 0.05f };
static float logoRotation = 0.0f;
static float backgroundScroll = 0.0f;
static float globalAlpha = 0.0f;
static Vector2 carPosition = { -100.0f, 0.0f };
static Rectangle buttonBounds[3];  // Hitboxes for buttons

// Update animation value with easing
static void UpdateAnimator(Animator *animator) {
    if (animator->value < animator->target) {
        animator->value += animator->speed;
        if (animator->value > animator->target) animator->value = animator->target;
    } else if (animator->value > animator->target) {
        animator->value -= animator->speed;
        if (animator->value < animator->target) animator->value = animator->target;
    }
}

// Draw a pixel art style car
static void DrawPixelCar(float posX, float posY, float scale, Color color) {
    // Car body
    DrawRectangle(posX, posY + 10*scale, 50*scale, 20*scale, color);
    
    // Car top
    DrawRectangle(posX + 10*scale, posY, 25*scale, 10*scale, color);
    
    // Windows
    DrawRectangle(posX + 12*scale, posY + 2*scale, 8*scale, 8*scale, SKYBLUE);
    DrawRectangle(posX + 25*scale, posY + 2*scale, 8*scale, 8*scale, SKYBLUE);
    
    // Wheels
    DrawCircle(posX + 10*scale, posY + 30*scale, 6*scale, BLACK);
    DrawCircle(posX + 10*scale, posY + 30*scale, 3*scale, GRAY);
    DrawCircle(posX + 40*scale, posY + 30*scale, 6*scale, BLACK);
    DrawCircle(posX + 40*scale, posY + 30*scale, 3*scale, GRAY);
}

// Draw pixel art style chicken (player character)
static void DrawPixelChicken(float posX, float posY, float scale, Color color) {
    // Body
    DrawRectangle(posX, posY + 10*scale, 20*scale, 15*scale, color);
    
    // Head
    DrawRectangle(posX + 2*scale, posY, 15*scale, 10*scale, color);
    
    // Beak
    DrawTriangle(
        (Vector2){posX + 17*scale, posY + 5*scale},
        (Vector2){posX + 25*scale, posY + 5*scale},
        (Vector2){posX + 17*scale, posY + 10*scale},
        GAME_YELLOW
    );
    
    // Eye
    DrawCircle(posX + 12*scale, posY + 5*scale, 2*scale, BLACK);
    
    // Legs
    DrawRectangle(posX + 5*scale, posY + 25*scale, 3*scale, 7*scale, GAME_YELLOW);
    DrawRectangle(posX + 15*scale, posY + 25*scale, 3*scale, 7*scale, GAME_YELLOW);
}

// Draw a button with hover effect
static bool DrawButton(const char *text, int posX, int posY, int fontSize, bool selected, int index) {
    int textWidth = MeasureText(text, fontSize);
    int buttonWidth = textWidth + 60;
    int buttonHeight = fontSize + 20;
    
    // Update button bounds for collision detection
    buttonBounds[index] = (Rectangle){ posX - buttonWidth/2, posY - buttonHeight/2, buttonWidth, buttonHeight };
    
    // Button background
    Color buttonColor = selected ? GAME_YELLOW : GAME_BLUE;
    DrawRectangle(posX - buttonWidth/2, posY - buttonHeight/2, buttonWidth, buttonHeight, buttonColor);
    
    // Button outline
    DrawRectangleLines(posX - buttonWidth/2, posY - buttonHeight/2, buttonWidth, buttonHeight, GAME_DARK);
    
    // Button shadow
    if (selected) {
        DrawRectangle(posX - buttonWidth/2 + 3, posY - buttonHeight/2 + 3, buttonWidth, buttonHeight, ColorAlpha(GAME_DARK, 0.3f));
    }
    
    // Button text
    DrawText(text, posX - textWidth/2, posY - fontSize/2, fontSize, selected ? GAME_DARK : GAME_LIGHT);
    
    // Return true if mouse is hovering over button
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, buttonBounds[index]);
}

// Draw road pattern
static void DrawRoadPattern(int screenWidth, int screenHeight, float scroll) {
    // Draw asphalt
    DrawRectangle(0, screenHeight - 100, screenWidth, 100, DARKGRAY);
    
    // Draw road lines
    for (int i = 0; i < screenWidth/50 + 1; i++) {
        int xPos = (i * 100 - (int)scroll % 100);
        DrawRectangle(xPos, screenHeight - 50 - 5, 40, 10, GAME_YELLOW);
    }
}

// Draw background elements
static void DrawBackground(int screenWidth, int screenHeight) {
    // Sky gradient
    DrawRectangleGradientV(0, 0, screenWidth, screenHeight, SKYBLUE, GAME_BLUE);
    
    // Draw some clouds
    DrawCircle(screenWidth * 0.2f + sin(backgroundScroll/100) * 20, screenHeight * 0.2f, 30, ColorAlpha(WHITE, 0.7f));
    DrawCircle(screenWidth * 0.2f + 20 + sin(backgroundScroll/100) * 20, screenHeight * 0.2f - 10, 25, ColorAlpha(WHITE, 0.7f));
    DrawCircle(screenWidth * 0.2f - 15 + sin(backgroundScroll/100) * 20, screenHeight * 0.2f + 5, 20, ColorAlpha(WHITE, 0.7f));
    
    DrawCircle(screenWidth * 0.7f + cos(backgroundScroll/120) * 20, screenHeight * 0.15f, 40, ColorAlpha(WHITE, 0.8f));
    DrawCircle(screenWidth * 0.7f + 30 + cos(backgroundScroll/120) * 20, screenHeight * 0.15f, 30, ColorAlpha(WHITE, 0.8f));
    DrawCircle(screenWidth * 0.7f - 25 + cos(backgroundScroll/120) * 20, screenHeight * 0.15f + 10, 25, ColorAlpha(WHITE, 0.8f));
    
    // Draw ground
    DrawRectangle(0, screenHeight - 120, screenWidth, 20, GAME_GREEN);
    
    // Draw road
    DrawRoadPattern(screenWidth, screenHeight, backgroundScroll);
}

MenuOption ShowMenu() {
    int selectedOption = 0;                                     
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    const char *menuOptions[] = {"Start Game", "Options", "Exit"};  
    int totalOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);
    
    // Reset animation variables
    titleBounce.value = 0.0f;
    titleBounce.target = 1.0f;
    globalAlpha = 0.0f;
    carPosition.x = -100.0f;
    carPosition.y = screenHeight - 150.0f;
    frameCounter = 0;
    backgroundScroll = 0.0f;
    
    for (int i = 0; i < totalOptions; i++) {
        buttonBounds[i] = (Rectangle){ 0, 0, 0, 0 };
    }
    
    // Play menu music
    if (!IsMusicStreamPlaying(menuBacksound) && isInMainMenu) {     
        PlayMenuBacksound();
    }    

    while (!WindowShouldClose()) {
        // Update animations
        frameCounter++;
        backgroundScroll += 1.0f;
        UpdateAnimator(&titleBounce);
        
        // Fade in effect
        if (globalAlpha < 1.0f) globalAlpha += 0.02f;
        if (globalAlpha > 1.0f) globalAlpha = 1.0f;
        
        // Logo bounce and spin effect
        float logoScale = 1.0f + sin(frameCounter / 20.0f) * 0.03f;
        logoRotation += 0.2f;
        if (logoRotation > 360.0f) logoRotation -= 360.0f;
        
        // Car animation
        carPosition.x += 3.0f;
        if (carPosition.x > screenWidth + 100) carPosition.x = -150.0f;
        
        // Mouse handling for buttons
        Vector2 mousePos = GetMousePosition();
        bool mouseOnButton = false;
        
        for (int i = 0; i < totalOptions; i++) {
            if (CheckCollisionPointRec(mousePos, buttonBounds[i])) {
                if (selectedOption != i) {
                    selectedOption = i;
                    menusound();
                }
                mouseOnButton = true;
                
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (selectedOption == 1) { 
                        isInMainMenu = true; 
                        return MENU_OPTIONS;    
                    }
                    return (MenuOption)selectedOption;
                }
            }
        }
        
        // Update music
        UpdateMusicStream(menuBacksound); 

        BeginDrawing();
            // Draw background
            DrawBackground(screenWidth, screenHeight);
            
            // Draw animated car
            DrawPixelCar(carPosition.x, carPosition.y, 1.5f, GAME_RED);
            
            // Draw player character on right side
            DrawPixelChicken(screenWidth - 120, screenHeight - 170, 2.0f, WHITE);
            
            // Draw title with bounce effect
            const char* title = "Crossing The Road";
            int titleFontSize = 50;
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
                // Calculate vertical position with slight delay between buttons
                float buttonY = (screenHeight/2 + 50) + i * 70;
                
                // Animate button appearance
                float buttonAppearDelay = i * 10;
                if (frameCounter < buttonAppearDelay) continue;
                
                float buttonAlpha = globalAlpha;
                if (frameCounter - buttonAppearDelay < 20) {
                    buttonAlpha = (frameCounter - buttonAppearDelay) / 20.0f * globalAlpha;
                }
                
                // Draw the button
                bool hover = DrawButton(
                    menuOptions[i], 
                    screenWidth/2, 
                    buttonY, 
                    30, 
                    i == selectedOption,
                    i
                );
            }
            
            
            // Copyright text
            const char* copyright = "© 2025 Your Game Studio";
            int copyrightWidth = MeasureText(copyright, 15);
            DrawText(copyright, 
                    (screenWidth - copyrightWidth)/2, 
                    screenHeight - 30, 
                    15, 
                    ColorAlpha(GAME_LIGHT, globalAlpha * 0.7f));
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
            if (selectedOption == 1) { 
                isInMainMenu = true; 
                return MENU_OPTIONS;    
            }
            return (MenuOption)selectedOption;
        }
    }

    return MENU_EXIT;
}