#include "../header.h"

// Variabel animasi UI internal (static)
static Animator titleBounceAnimator = { 0.0f, 1.0f, 0.05f };
static float uiLogoRotation = 0.0f;
static float uiBackgroundScroll = 0.0f;
static float uiGlobalAlpha = 0.0f;
static Vector2 uiCarPosition = { -100.0f, 0.0f };
static unsigned int uiFrameCounter = 0; // Frame counter khusus untuk animasi UI

// Helper functions (static, karena hanya dipakai di file ini)

// Update animation value with easing
static void UpdateAnimatorInternal(Animator *animator) {
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
    DrawRectangle(posX, posY + 10*scale, 50*scale, 20*scale, color);
    DrawRectangle(posX + 10*scale, posY, 25*scale, 10*scale, color);
    DrawRectangle(posX + 12*scale, posY + 2*scale, 8*scale, 8*scale, SKYBLUE);
    DrawRectangle(posX + 25*scale, posY + 2*scale, 8*scale, 8*scale, SKYBLUE);
    DrawCircle(posX + 10*scale, posY + 30*scale, 6*scale, BLACK);
    DrawCircle(posX + 10*scale, posY + 30*scale, 3*scale, GRAY);
    DrawCircle(posX + 40*scale, posY + 30*scale, 6*scale, BLACK);
    DrawCircle(posX + 40*scale, posY + 30*scale, 3*scale, GRAY);
}

// Draw pixel art style chicken (player character)
static void DrawPixelChicken(float posX, float posY, float scale, Color color) {
    DrawRectangle(posX, posY + 10*scale, 20*scale, 15*scale, color);
    DrawRectangle(posX + 2*scale, posY, 15*scale, 10*scale, color);
    DrawTriangle(
        (Vector2){posX + 17*scale, posY + 5*scale},
        (Vector2){posX + 25*scale, posY + 5*scale},
        (Vector2){posX + 17*scale, posY + 10*scale},
        GAME_YELLOW
    );
    DrawCircle(posX + 12*scale, posY + 5*scale, 2*scale, BLACK);
    DrawRectangle(posX + 5*scale, posY + 25*scale, 3*scale, 7*scale, GAME_YELLOW);
    DrawRectangle(posX + 15*scale, posY + 25*scale, 3*scale, 7*scale, GAME_YELLOW);
}

// Draw road pattern
static void DrawRoadPattern(int screenWidth, int screenHeight, float scroll) {
    DrawRectangle(0, screenHeight - 100, screenWidth, 100, DARKGRAY);
    for (int i = 0; i < screenWidth/50 + 2; i++) { // +2 untuk memastikan menutupi saat scroll
        int xPos = (i * 100 - (int)scroll % 100) - 50; // offset agar mulai dari sebelum layar
        DrawRectangle(xPos, screenHeight - 50 - 5, 40, 10, GAME_YELLOW);
    }
}

// Draw background elements
static void DrawBackgroundElements(int screenWidth, int screenHeight, float scroll) {
    DrawRectangleGradientV(0, 0, screenWidth, screenHeight, SKYBLUE, GAME_BLUE);
    
    // Awan dengan sedikit variasi posisi berdasarkan scroll untuk efek parallax sederhana
    float cloudScrollEffect1 = sin(scroll / 150.0f) * 10;
    float cloudScrollEffect2 = cos(scroll / 180.0f) * 15;

    DrawCircle(screenWidth * 0.2f + cloudScrollEffect1, screenHeight * 0.2f, 30, ColorAlpha(WHITE, 0.7f * uiGlobalAlpha));
    DrawCircle(screenWidth * 0.2f + 20 + cloudScrollEffect1, screenHeight * 0.2f - 10, 25, ColorAlpha(WHITE, 0.7f * uiGlobalAlpha));
    DrawCircle(screenWidth * 0.2f - 15 + cloudScrollEffect1, screenHeight * 0.2f + 5, 20, ColorAlpha(WHITE, 0.7f * uiGlobalAlpha));
    
    DrawCircle(screenWidth * 0.7f + cloudScrollEffect2, screenHeight * 0.15f, 40, ColorAlpha(WHITE, 0.8f * uiGlobalAlpha));
    DrawCircle(screenWidth * 0.7f + 30 + cloudScrollEffect2, screenHeight * 0.15f, 30, ColorAlpha(WHITE, 0.8f * uiGlobalAlpha));
    DrawCircle(screenWidth * 0.7f - 25 + cloudScrollEffect2, screenHeight * 0.15f + 10, 25, ColorAlpha(WHITE, 0.8f * uiGlobalAlpha));
    
    DrawRectangle(0, screenHeight - 120, screenWidth, 20, GAME_GREEN);
    DrawRoadPattern(screenWidth, screenHeight, scroll);
}

// Implementasi fungsi yang dideklarasikan di .h
void UpdateUIAnimator(Animator *animator) {
    UpdateAnimatorInternal(animator);
}

void InitUIElements(int screenWidth, int screenHeight) {
    titleBounceAnimator.value = 0.0f;
    titleBounceAnimator.target = 1.0f;
    // titleBounceAnimator.speed sudah diinisialisasi di atas
    
    uiGlobalAlpha = 0.0f;
    uiCarPosition.x = -100.0f; // Mulai dari luar layar kiri
    uiCarPosition.y = screenHeight - 150.0f; // Posisi Y mobil disesuaikan dengan tinggi layar
    uiFrameCounter = 0;
    uiBackgroundScroll = 0.0f;
    uiLogoRotation = 0.0f; // Jika ada logo yang berputar
}

void UpdateUIElements(int screenWidth, int screenHeight) {
    uiFrameCounter++;
    uiBackgroundScroll += 1.0f; // Kecepatan gulir latar belakang
    UpdateAnimatorInternal(&titleBounceAnimator);
    
    if (uiGlobalAlpha < 1.0f) uiGlobalAlpha += 0.02f;
    if (uiGlobalAlpha > 1.0f) uiGlobalAlpha = 1.0f;
    
    // Jika ada logo bersama, animasinya bisa di sini
    // float logoScale = 1.0f + sin(uiFrameCounter / 20.0f) * 0.03f * titleBounceAnimator.value;
    uiLogoRotation += 0.2f;
    if (uiLogoRotation > 360.0f) uiLogoRotation -= 360.0f;
    
    uiCarPosition.x += 3.0f; // Kecepatan mobil
    if (uiCarPosition.x > screenWidth + 100) { // Jika mobil keluar layar kanan
        uiCarPosition.x = -150.0f; // Reset ke kiri luar layar
        // Anda bisa menambahkan variasi pada Y atau warna mobil di sini jika mau
        uiCarPosition.y = screenHeight - 150.0f + (GetRandomValue(-10, 10)); // Sedikit variasi Y
    }
}

void DrawSharedUILayout(int screenWidth, int screenHeight, const char *title, const char *subtitle, bool drawChicken) {
    // Gambar Latar Belakang
    DrawBackgroundElements(screenWidth, screenHeight, uiBackgroundScroll);
    
    // Gambar Mobil Animasi
    DrawPixelCar(uiCarPosition.x, uiCarPosition.y, 1.5f, ColorAlpha(GAME_RED, uiGlobalAlpha));
    
    // Gambar Karakter Ayam (jika diminta)
    if (drawChicken) {
        DrawPixelChicken(screenWidth - 120, screenHeight - 170, 2.0f, ColorAlpha(WHITE, uiGlobalAlpha));
    }
    
    // Gambar Judul dengan efek pantul dan fade-in
    if (title) {
        int titleFontSize = 30;
        int titleWidth = MeasureText(title, titleFontSize);
        float titleY = screenHeight/4 - 50 + sin(uiFrameCounter/10.0f) * 5.0f * titleBounceAnimator.value;
        
        // Bayangan Judul
        DrawText(title, (screenWidth - titleWidth)/2 + 4, titleY + 4, 
                 titleFontSize, ColorAlpha(GAME_DARK, 0.5f * uiGlobalAlpha));
        // Judul Utama
        DrawText(title, (screenWidth - titleWidth)/2, titleY, 
                 titleFontSize, ColorAlpha(GAME_YELLOW, uiGlobalAlpha));
    }

    // Gambar Subjudul dengan efek dan fade-in
    if (subtitle) {
        int subtitleFontSize = 20;
        int subtitleWidth = MeasureText(subtitle, subtitleFontSize);
        float subtitleY = screenHeight/4 + 10 + sin(uiFrameCounter/10.0f) * 5.0f * titleBounceAnimator.value;

        DrawText(subtitle, (screenWidth - subtitleWidth)/2, subtitleY, 
                 subtitleFontSize, ColorAlpha(GAME_LIGHT, uiGlobalAlpha));
    }
}

void DrawCopyright(int screenWidth, int screenHeight) {
    const char* copyright = "© 2025 ProjectB6 Studio Corp"; // Ganti dengan teks Anda
    int copyrightFontSize = 15;
    int copyrightWidth = MeasureText(copyright, copyrightFontSize);
    DrawText(copyright, 
             (screenWidth - copyrightWidth)/2, 
             screenHeight - 30, 
             copyrightFontSize, 
             ColorAlpha(GAME_LIGHT, uiGlobalAlpha * 0.7f));
}

float GetUIGlobalAlpha(void) {
    return uiGlobalAlpha;
}