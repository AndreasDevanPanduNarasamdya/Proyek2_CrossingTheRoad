#include "raylib.h"

// Fungsi untuk menampilkan menu Options
void ShowOptions(float *volume, bool *isFullscreen) {
    while (!WindowShouldClose()) {
        // Bersihkan layar sebelum menggambar
        ClearBackground(RAYWHITE);

        // Hitung posisi teks agar rata tengah
        int fontSize = 20;
        int textWidth = MeasureText("Fullscreen", fontSize);
        int buttonWidth = 200;
        int buttonHeight = 40;
        int buttonX = (GetScreenWidth() - buttonWidth) / 2;
        int buttonY = 200;

        // Tampilkan teks judul "Options"
        DrawText("Options", GetScreenWidth() / 2 - MeasureText("Options", 30) / 2, 50, 30, DARKGRAY);

        // Tampilkan pengaturan Volume
        DrawText(TextFormat("Volume: %d%%", (int)(*volume * 100)), GetScreenWidth() / 2 - MeasureText("Volume: 100%", fontSize) / 2, 120, fontSize, BLACK);

        // Gambar tombol "Fullscreen"
        DrawRectangle(buttonX, buttonY, buttonWidth, buttonHeight, RED);
        DrawText("Fullscreen", buttonX + (buttonWidth - textWidth) / 2, buttonY + 10, fontSize, BLACK);
        DrawText(*isFullscreen ? "ON" : "OFF", buttonX + buttonWidth + 20, buttonY + 10, fontSize, BLACK);

        // Tombol kembali
        DrawText("Back to Main Menu", GetScreenWidth() / 2 - MeasureText("Back to Main Menu", fontSize) / 2, 300, fontSize, BLACK);

        // Perbarui tampilan
        EndDrawing();
    }
}
