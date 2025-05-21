#include "../header.h"

// Animator struct (copied from main menu)
typedef struct {
    float value;         // Current value
    float target;        // Target value
    float speed;         // Animation speed
} Animator;

// Cloud animation struct
typedef struct {
    Vector2 position;
    float speed;
    float size;
    float alpha;
} Cloud;

// Global variables
static Animator titleBounce = { 0.0f, 1.0f, 0.05f };
static float globalAlpha = 0.0f;
static int frameCounter = 0;
static Rectangle buttonBounds[3];  // Hitboxes for buttons
static Cloud clouds[5];  // Array of clouds

// Update animation value with easing (copied from main menu)
static void UpdateAnimator(Animator *animator) {
    if (animator->value < animator->target) {
        animator->value += animator->speed;
        if (animator->value > animator->target) animator->value = animator->target;
    } else if (animator->value > animator->target) {
        animator->value -= animator->speed;
        if (animator->value < animator->target) animator->value = animator->target;
    }
}

// Draw a cloud with multiple circles
static void DrawCloud(Cloud cloud) {
    Color cloudColor = ColorAlpha(WHITE, cloud.alpha);
    float size = cloud.size;
    
    DrawCircle(cloud.position.x, cloud.position.y, size * 0.8f, cloudColor);
    DrawCircle(cloud.position.x + size * 0.7f, cloud.position.y - size * 0.2f, size * 0.6f, cloudColor);
    DrawCircle(cloud.position.x + size * 1.2f, cloud.position.y, size * 0.9f, cloudColor);
    DrawCircle(cloud.position.x + size * 0.3f, cloud.position.y + size * 0.4f, size * 0.7f, cloudColor);
}

// Initialize clouds
static void InitClouds(int screenWidth, int screenHeight) {
    for (int i = 0; i < 5; i++) {
        clouds[i].position.x = GetRandomValue(0, screenWidth);
        clouds[i].position.y = GetRandomValue(20, screenHeight / 3);
        clouds[i].speed = GetRandomValue(5, 15) / 10.0f;
        clouds[i].size = GetRandomValue(20, 40);
        clouds[i].alpha = GetRandomValue(60, 90) / 100.0f;
    }
}

// Update cloud positions
static void UpdateClouds(int screenWidth) {
    for (int i = 0; i < 5; i++) {
        clouds[i].position.x += clouds[i].speed;
        
        // Reset cloud when it goes off screen
        if (clouds[i].position.x > screenWidth + clouds[i].size * 2) {
            clouds[i].position.x = -clouds[i].size * 2;
            clouds[i].position.y = GetRandomValue(20, GetScreenHeight() / 3);
        }
    }
}

// Draw a button with hover effect (similar to main menu)
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

void ShowOptions(float *volume, bool *isFullscreen) {
    int selectedOption = 0;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    
    // Reset animation variables
    titleBounce.value = 0.0f;
    titleBounce.target = 1.0f;
    globalAlpha = 0.0f;
    frameCounter = 0;
    
    // Initialize cloud positions
    InitClouds(screenWidth, screenHeight);
    
    // Initialize button bounds
    for (int i = 0; i < 3; i++) {
        buttonBounds[i] = (Rectangle){ 0, 0, 0, 0 };
    }

    while (!WindowShouldClose()) {
        // Update animations
        frameCounter++;
        UpdateAnimator(&titleBounce);
        UpdateClouds(screenWidth);
        
        // Fade in effect
        if (globalAlpha < 1.0f) globalAlpha += 0.02f;
        if (globalAlpha > 1.0f) globalAlpha = 1.0f;
        
        // Update music
        UpdateMusicStream(menuBacksound);
        
        // Mouse handling for buttons
        Vector2 mousePos = GetMousePosition();
        bool mouseOnButton = false;
        
        for (int i = 0; i < 3; i++) {
            if (CheckCollisionPointRec(mousePos, buttonBounds[i])) {
                if (selectedOption != i) {
                    selectedOption = i;
                    menusound();  // Play menu sound effect
                }
                mouseOnButton = true;
                
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (selectedOption == 0) {
                        // Volume control via mouse click - left half decreases, right half increases
                        float clickX = mousePos.x - buttonBounds[0].x;
                        float ratio = clickX / buttonBounds[0].width;
                        
                        if (ratio < 0.5f) {
                            *volume -= 0.05f;
                            if (*volume < 0.0f) *volume = 0.0f;
                        } else {
                            *volume += 0.05f;
                            if (*volume > 1.0f) *volume = 1.0f;
                        }
                        SetMasterVolume(*volume);
                    } else if (selectedOption == 1) {
                        *isFullscreen = !(*isFullscreen);
                        ToggleFullscreen();
                    } else if (selectedOption == 2) {
                        return;  // Return to main menu
                    }
                }
            }
        }

        BeginDrawing();
            // Draw sky background (gradient like main menu)
            DrawRectangleGradientV(0, 0, screenWidth, screenHeight, SKYBLUE, GAME_BLUE);
            
            // Draw animated clouds
            for (int i = 0; i < 5; i++) {
                DrawCloud(clouds[i]);
            }
            
            // Draw title with bounce effect
            const char* title = "OPTIONS";
            int titleFontSize = 50;
            int titleWidth = MeasureText(title, titleFontSize);
            
            // Title shadow
            DrawText(title, (screenWidth - titleWidth)/2 + 4, 80 + 4, 
                    titleFontSize, ColorAlpha(GAME_DARK, 0.5f * globalAlpha));
                    
            // Title with bounce effect
            DrawText(title, (screenWidth - titleWidth)/2, 80 + sin(frameCounter/10.0f) * 5.0f, 
                    titleFontSize, ColorAlpha(GAME_YELLOW, globalAlpha));
            
            // Menu Options (Buttons)
            const char *menuItems[] = {
                TextFormat("Volume: %d%%", (int)(*volume * 100)),
                TextFormat("Fullscreen: %s", *isFullscreen ? "ON" : "OFF"),
                "Back"
            };
            
            for (int i = 0; i < 3; i++) {
                // Calculate vertical position with slight delay between buttons
                float buttonY = (screenHeight/2) + i * 70;
                
                // Animate button appearance
                float buttonAppearDelay = i * 10;
                if (frameCounter < buttonAppearDelay) continue;
                
                float buttonAlpha = globalAlpha;
                if (frameCounter - buttonAppearDelay < 20) {
                    buttonAlpha = (frameCounter - buttonAppearDelay) / 20.0f * globalAlpha;
                }
                
                // Draw the button
                bool hover = DrawButton(
                    menuItems[i], 
                    screenWidth/2, 
                    buttonY, 
                    30, 
                    i == selectedOption,
                    i
                );
            }
            
            // Volume adjustment hint
            if (selectedOption == 0) {
                const char* hint = "< Press LEFT/RIGHT to adjust >";
                int hintWidth = MeasureText(hint, 20);
                DrawText(hint, (screenWidth - hintWidth)/2, (screenHeight/2) + 40, 20, ColorAlpha(WHITE, 0.7f));
            }
        EndDrawing();
        
        // Keyboard navigation
        if (IsKeyPressed(KEY_DOWN)) {
            selectedOption = (selectedOption + 1) % 3;
            menusound();  // Play menu sound effect
        }
        
        if (IsKeyPressed(KEY_UP)) {
            selectedOption = (selectedOption - 1 + 3) % 3;
            menusound();  // Play menu sound effect
        }
        
        // Volume control
        if (selectedOption == 0) {
            if (IsKeyDown(KEY_LEFT)) {
                *volume -= 0.01f;
                if (*volume < 0.0f) *volume = 0.0f;
                SetMasterVolume(*volume);
            }
            if (IsKeyDown(KEY_RIGHT)) {
                *volume += 0.01f;
                if (*volume > 1.0f) *volume = 1.0f;
                SetMasterVolume(*volume);
            }
        }
        
        // Enter key
        if (IsKeyPressed(KEY_ENTER)) {
            if (selectedOption == 1) {
                *isFullscreen = !(*isFullscreen);
                ToggleFullscreen();
            } else if (selectedOption == 2) {
                return;  // Return to main menu
            }
        }
    }
}