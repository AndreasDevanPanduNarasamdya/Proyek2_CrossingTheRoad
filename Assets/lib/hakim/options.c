#include "../header.h"

// Custom utility functions - not marked static since they're used in functions that are static
float Clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

Color ColorLerp(Color a, Color b, float t) {
    t = Clamp(t, 0.0f, 1.0f);
    return (Color){
        (unsigned char)(a.r + (b.r - a.r) * t),
        (unsigned char)(a.g + (b.g - a.g) * t),
        (unsigned char)(a.b + (b.b - a.b) * t),
        (unsigned char)(a.a + (b.a - a.a) * t)
    };
}

// Slider animation variables
typedef struct {
    Rectangle bounds;
    float value;
    bool dragging;
    Color sliderColor;
    Color backgroundColor;
} Slider;

// Toggle animation variables
typedef struct {
    Rectangle bounds;
    bool value;
    float animationValue;
    Color activeColor;
    Color inactiveColor;
} Toggle;

// Helper function to update slider
static void UpdateSlider(Slider *slider, float *value, float min, float max) {
    Vector2 mousePoint = GetMousePosition();
    
    // Check if mouse is over slider
    bool mouseOver = CheckCollisionPointRec(mousePoint, slider->bounds);
    
    // Update drag state
    if (mouseOver && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        slider->dragging = true;
    else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        slider->dragging = false;
    
    // Update value based on drag position
    if (slider->dragging) {
        float newValue = (mousePoint.x - slider->bounds.x) / slider->bounds.width;
        newValue = Clamp(newValue, 0.0f, 1.0f);
        *value = min + newValue * (max - min);
        slider->value = newValue;
    } else {
        slider->value = (*value - min) / (max - min);
    }
}

// Helper function to draw slider
static void DrawSlider(Slider slider, const char *label, float value, int fontSize) {
    // Draw slider background
    DrawRectangleRec(slider.bounds, slider.backgroundColor);
    
    // Draw filled slider
    DrawRectangle(slider.bounds.x, slider.bounds.y, 
                 slider.bounds.width * slider.value, slider.bounds.height, 
                 slider.sliderColor);
    
    // Draw slider outline
    DrawRectangleLinesEx(slider.bounds, 2, (Color){ 49, 55, 65, 255 });
    
    // Draw label
    DrawText(label, slider.bounds.x, slider.bounds.y - fontSize - 10, fontSize, WHITE);
    
    // Draw value
    char valueText[32];
    sprintf(valueText, "%d%%", (int)(value * 100));
    int textWidth = MeasureText(valueText, fontSize);
    DrawText(valueText, slider.bounds.x + slider.bounds.width + 20, 
             slider.bounds.y + (slider.bounds.height - fontSize)/2, fontSize, WHITE);
}

// Helper function to update toggle
static void UpdateToggle(Toggle *toggle, bool *value) {
    Vector2 mousePoint = GetMousePosition();
    
    // Check if mouse is over toggle
    bool mouseOver = CheckCollisionPointRec(mousePoint, toggle->bounds);
    
    // Update state on click
    if (mouseOver && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        *value = !(*value);
        toggle->value = *value;
    }
    
    // Update animation value
    if (toggle->value) {
        toggle->animationValue += 0.1f;
        if (toggle->animationValue > 1.0f) toggle->animationValue = 1.0f;
    } else {
        toggle->animationValue -= 0.1f;
        if (toggle->animationValue < 0.0f) toggle->animationValue = 0.0f;
    }
}

// Helper function to draw toggle
static void DrawToggle(Toggle toggle, const char *label, bool value, int fontSize) {
    // Background
    Color backgroundColor = ColorLerp(toggle.inactiveColor, toggle.activeColor, toggle.animationValue);
    DrawRectangleRec(toggle.bounds, backgroundColor);
    
    // Knob
    float knobSize = toggle.bounds.height - 4;
    float knobX = toggle.bounds.x + 2 + (toggle.bounds.width - knobSize - 4) * toggle.animationValue;
    DrawRectangle(knobX, toggle.bounds.y + 2, knobSize, knobSize, WHITE);
    
    // Draw toggle outline
    DrawRectangleLinesEx(toggle.bounds, 2, (Color){ 49, 55, 65, 255 });
    
    // Draw label
    DrawText(label, toggle.bounds.x, toggle.bounds.y - fontSize - 10, fontSize, WHITE);
    
    // Draw status
    char statusText[8];
    sprintf(statusText, "%s", value ? "ON" : "OFF");
    int textWidth = MeasureText(statusText, fontSize);
    DrawText(statusText, toggle.bounds.x + toggle.bounds.width + 20, 
             toggle.bounds.y + (toggle.bounds.height - fontSize)/2, fontSize, WHITE);
}

// Helper function to draw button - fixed parameter types
static bool DrawOptionButton(const char *text, Rectangle bounds, bool selected, Color color) {
    Vector2 mousePoint = GetMousePosition();
    bool mouseOver = CheckCollisionPointRec(mousePoint, bounds);
    
    // Draw background
    Color buttonColor = selected ? color : (Color){ color.r*0.8f, color.g*0.8f, color.b*0.8f, color.a };
    DrawRectangleRec(bounds, buttonColor);
    
    // Draw outline
    DrawRectangleLinesEx(bounds, 2, (Color){ 49, 55, 65, 255 });
    
    // Draw shadow
    if (selected || mouseOver) {
        DrawRectangle(bounds.x + 3, bounds.y + 3, bounds.width, bounds.height, 
                     (Color){ 0, 0, 0, 50 });
    }
    
    // Draw text
    int fontSize = 24;
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, bounds.x + (bounds.width - textWidth)/2, 
             bounds.y + (bounds.height - fontSize)/2, fontSize, WHITE);
    
    return mouseOver;
}

// Helper function to draw road pattern - renamed to avoid redefinition
static void DrawOptionRoadPattern(int screenWidth, int screenHeight, float scroll) {
    // Draw asphalt
    DrawRectangle(0, screenHeight - 100, screenWidth, 100, (Color){ 45, 45, 45, 255 });
    
    // Draw road lines
    for (int i = 0; i < screenWidth/50 + 1; i++) {
        int xPos = (i * 100 - (int)scroll % 100);
        DrawRectangle(xPos, screenHeight - 50 - 5, 40, 10, (Color){ 255, 207, 64, 255 });
    }
}

// Helper function to draw clouds
static void DrawClouds(int screenWidth, int screenHeight, float time) {
    // Draw some clouds
    DrawCircle(screenWidth * 0.2f + sin(time/100) * 20, screenHeight * 0.2f, 30, (Color){ 255, 255, 255, 180 });
    DrawCircle(screenWidth * 0.2f + 20 + sin(time/100) * 20, screenHeight * 0.2f - 10, 25, (Color){ 255, 255, 255, 180 });
    DrawCircle(screenWidth * 0.2f - 15 + sin(time/100) * 20, screenHeight * 0.2f + 5, 20, (Color){ 255, 255, 255, 180 });
    
    DrawCircle(screenWidth * 0.7f + cos(time/120) * 20, screenHeight * 0.15f, 40, (Color){ 255, 255, 255, 200 });
    DrawCircle(screenWidth * 0.7f + 30 + cos(time/120) * 20, screenHeight * 0.15f, 30, (Color){ 255, 255, 255, 200 });
    DrawCircle(screenWidth * 0.7f - 25 + cos(time/120) * 20, screenHeight * 0.15f + 10, 25, (Color){ 255, 255, 255, 200 });
}

// Helper function to draw pixel art style car - renamed to avoid redefinition
static void DrawOptionPixelCar(float posX, float posY, float scale, Color color) {
    // Car body
    DrawRectangle(posX, posY + 10*scale, 50*scale, 20*scale, color);
    
    // Car top
    DrawRectangle(posX + 10*scale, posY, 25*scale, 10*scale, color);
    
    // Windows
    DrawRectangle(posX + 12*scale, posY + 2*scale, 8*scale, 8*scale, (Color){ 130, 200, 255, 255 });
    DrawRectangle(posX + 25*scale, posY + 2*scale, 8*scale, 8*scale, (Color){ 130, 200, 255, 255 });
    
    // Wheels
    DrawCircle(posX + 10*scale, posY + 30*scale, 6*scale, BLACK);
    DrawCircle(posX + 10*scale, posY + 30*scale, 3*scale, GRAY);
    DrawCircle(posX + 40*scale, posY + 30*scale, 6*scale, BLACK);
    DrawCircle(posX + 40*scale, posY + 30*scale, 3*scale, GRAY);
}

void ShowOptions(float *volume, bool *isFullscreen) {       
    int selectedOption = 0;
    float backgroundScroll = 0.0f;
    float animationTimer = 0.0f;
    Vector2 carPosition = { -100.0f, 0.0f };
    bool carMovingRight = true;
    
    // Initialize UI components
    Slider volumeSlider = {
        (Rectangle){ SCREEN_WIDTH / 2 - 150, 160, 300, 30 },
        *volume,
        false,
        (Color){ 255, 97, 97, 255 },    // Red slider
        (Color){ 80, 80, 80, 255 }      // Dark gray background
    };
    
    Toggle fullscreenToggle = {
        (Rectangle){ SCREEN_WIDTH / 2 - 150, 240, 70, 30 },
        *isFullscreen,
        *isFullscreen ? 1.0f : 0.0f,
        (Color){ 87, 201, 111, 255 },   // Green when active
        (Color){ 80, 80, 80, 255 }      // Dark gray when inactive
    };
    
    Rectangle backButton = {
        SCREEN_WIDTH / 2 - 100,
        320,
        200,
        50
    };
    
    // Color scheme
    Color bgColorTop = (Color){ 76, 157, 240, 255 };      // Sky blue
    Color bgColorBottom = (Color){ 87, 201, 111, 255 };   // Green
    Color titleColor = (Color){ 255, 207, 64, 255 };      // Yellow
    Color buttonColor = (Color){ 185, 102, 235, 255 };    // Purple
    
    while (!WindowShouldClose()) {
        UpdateMusicStream(menuBacksound);
        
        // Update animations
        backgroundScroll += 1.0f;
        animationTimer += 0.05f;
        
        // Car animation
        if (carMovingRight) {
            carPosition.x += 3.0f;
            if (carPosition.x > SCREEN_WIDTH + 100) {
                carMovingRight = false;
                carPosition.x = SCREEN_WIDTH + 100;
            }
        } else {
            carPosition.x -= 3.0f;
            if (carPosition.x < -100) {
                carMovingRight = true;
                carPosition.x = -100;
            }
        }
        carPosition.y = SCREEN_HEIGHT - 150.0f;
        
        // Update volume slider
        UpdateSlider(&volumeSlider, volume, 0.0f, 1.0f);
        SetMasterVolume(*volume); // Apply volume changes
        
        // Update fullscreen toggle
        UpdateToggle(&fullscreenToggle, isFullscreen);
        
        // Mouse interaction for back button
        Vector2 mousePoint = GetMousePosition();
        bool backButtonHover = CheckCollisionPointRec(mousePoint, backButton);
        
        if (backButtonHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            return;
        }
        
        // Keyboard navigation
        if (IsKeyPressed(KEY_DOWN)) {
            selectedOption = (selectedOption + 1) % 3;
            menusound();
        }
        if (IsKeyPressed(KEY_UP)) {
            selectedOption = (selectedOption - 1 + 3) % 3;
            menusound();
        }
        
        // Handle volume changes with keyboard
        if (selectedOption == 0) {
            if (IsKeyDown(KEY_LEFT) && *volume > 0.0f) {
                *volume -= 0.01f;
                if (*volume < 0.0f) *volume = 0.0f;
                volumeSlider.value = *volume;
                SetMasterVolume(*volume);
            }
            if (IsKeyDown(KEY_RIGHT) && *volume < 1.0f) {
                *volume += 0.01f;
                if (*volume > 1.0f) *volume = 1.0f;
                volumeSlider.value = *volume;
                SetMasterVolume(*volume);
            }
        }
        
        // Handle enter key presses
        if (IsKeyPressed(KEY_ENTER)) {
            if (selectedOption == 1) {
                *isFullscreen = !(*isFullscreen);
                fullscreenToggle.value = *isFullscreen;
                ToggleFullscreen();
            } else if (selectedOption == 2) {
                return;
            }
        }
        
        BeginDrawing();
            // Background gradient
            DrawRectangleGradientV(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, bgColorTop, bgColorBottom);
            
            // Draw decorative elements
            DrawClouds(SCREEN_WIDTH, SCREEN_HEIGHT, animationTimer);
            DrawOptionRoadPattern(SCREEN_WIDTH, SCREEN_HEIGHT, backgroundScroll);
            
            // Draw animated car
            DrawOptionPixelCar(carPosition.x, carPosition.y, 1.5f, (Color){ 255, 97, 97, 255 });
            
            // Draw title panel
            DrawRectangle(SCREEN_WIDTH/2 - 200, 40, 400, 60, (Color){ 49, 55, 65, 200 });
            DrawRectangleLinesEx((Rectangle){ SCREEN_WIDTH/2 - 200, 40, 400, 60 }, 2, (Color){ 255, 255, 255, 100 });
            
            // Draw title with bounce effect
            DrawText("OPTIONS",
                     SCREEN_WIDTH/2 - MeasureText("OPTIONS", 40)/2,
                     50 + sin(animationTimer) * 3,
                     40,
                     titleColor);
            
            // Draw panel for options
            DrawRectangle(SCREEN_WIDTH/2 - 200, 120, 400, 280, (Color){ 49, 55, 65, 200 });
            DrawRectangleLinesEx((Rectangle){ SCREEN_WIDTH/2 - 200, 120, 400, 280 }, 2, (Color){ 255, 255, 255, 100 });
            
            // Draw volume slider
            DrawSlider(volumeSlider, "VOLUME", *volume, 20);
            
            // Draw fullscreen toggle
            DrawToggle(fullscreenToggle, "FULLSCREEN", *isFullscreen, 20);
            
            // Draw back button
            bool backHighlight = DrawOptionButton("BACK", backButton, selectedOption == 2, buttonColor);
            
            // Draw selection indicator for keyboard navigation
            if (selectedOption == 0) {
                DrawRectangleLinesEx(
                    (Rectangle){ volumeSlider.bounds.x - 10, volumeSlider.bounds.y - 10,
                                volumeSlider.bounds.width + 20, volumeSlider.bounds.height + 20 },
                    3, YELLOW);
            } else if (selectedOption == 1) {
                DrawRectangleLinesEx(
                    (Rectangle){ fullscreenToggle.bounds.x - 10, fullscreenToggle.bounds.y - 10,
                                fullscreenToggle.bounds.width + 20, fullscreenToggle.bounds.height + 20 },
                    3, YELLOW);
            }
            
            // Draw controls hint
            DrawText("Use arrow keys to navigate and adjust settings",
                    SCREEN_WIDTH/2 - MeasureText("Use arrow keys to navigate and adjust settings", 15)/2,
                    SCREEN_HEIGHT - 30,
                    15,
                    WHITE);
                    
        EndDrawing();
    }
}