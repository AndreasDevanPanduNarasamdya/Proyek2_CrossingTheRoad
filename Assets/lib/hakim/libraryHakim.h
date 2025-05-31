#ifndef LIBRARY_HAKIM_H
#define LIBRARY_HAKIM_H

#include <stdbool.h>
#include "../header.h"

/// ====== menu.h ======
typedef enum {              
    MENU_START,
    MENU_OPTIONS,
    MENU_EXIT
} MenuOption;

bool isInMainMenu = true;

    MenuOption ShowMenu(); 


/// ====== options.h ======
void ShowOptions(float *volume, bool *isFullscreen);

/// ====== pause.h ======
void HandlePause(bool *isPaused, bool *isInMainMenu, float *volume, bool *isFullscreen);

/// ====== tryagain.h ======
void ShowTryAgain(bool *restartGame);
void HandleGameOver(bool *kalah, bool *PermainanBerakhir, Camera2D *camera, Checkpoint *Home, HealthHP *Health, PointsXP *Points, EggyPoints *Egg);

/// ====== ui.h ======
#define GAME_GREEN      (Color){ 87, 201, 111, 255 }
#define GAME_BLUE       (Color){ 76, 157, 240, 255 }
#define GAME_YELLOW     (Color){ 255, 207, 64, 255 }
#define GAME_RED        (Color){ 255, 97, 97, 255 }
#define GAME_PURPLE     (Color){ 185, 102, 235, 255 }
#define GAME_DARK       (Color){ 49, 55, 65, 255 }
#define GAME_LIGHT      (Color){ 245, 245, 245, 255 }
// Pastikan SKYBLUE dan warna lain seperti BLACK, GRAY, WHITE juga terdefinisi
// atau ganti dengan definisi raylib seperti RAYWHITE

// Animation variables structure
typedef struct {
    float value;        // Current value
    float target;       // Target value
    float speed;        // Animation speed
} Animator;

// Fungsi untuk menginisialisasi elemen UI dan animasinya
void InitUIElements(int screenWidth, int screenHeight);

// Fungsi untuk memperbarui logika animasi elemen UI
void UpdateUIElements(int screenWidth, int screenHeight);

// Fungsi untuk menggambar layout UI yang digunakan bersama
// Termasuk latar belakang, mobil, ayam (opsional), judul, dan subjudul
void DrawSharedUILayout(int screenWidth, int screenHeight, const char *title, const char *subtitle, bool drawChicken);

// Fungsi untuk menggambar teks hak cipta
void DrawCopyright(int screenWidth, int screenHeight);

// Fungsi utilitas untuk memperbarui animator (bisa tetap static di .c jika hanya dipakai di sana,
// atau dideklarasikan di sini jika akan dipakai di luar ui_elements.c)
void UpdateUIAnimator(Animator *animator);

// Fungsi untuk mendapatkan nilai alpha global saat ini (jika diperlukan oleh modul lain)
float GetUIGlobalAlpha(void);

#endif 
