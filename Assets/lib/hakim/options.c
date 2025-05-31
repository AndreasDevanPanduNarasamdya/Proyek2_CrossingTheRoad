#include "../header.h"

static Rectangle DrawOptionItem(const char *text, int posX, int posY, int fontSize, bool selected, float alpha, Color defaultColor, Color selectedColor) {
    Color currentColor = selected ? selectedColor : defaultColor;
    int textWidth = MeasureText(text, fontSize);
    int textHeight = fontSize; // Perkiraan tinggi teks

    // Posisi teks di tengah secara horizontal dan vertikal
    int drawPosX = posX - textWidth / 2;
    int drawPosY = posY - textHeight / 2;

    DrawText(text, drawPosX, drawPosY, fontSize, ColorAlpha(currentColor, alpha));

    // Hitbox dengan sedikit padding
    return (Rectangle){
        (float)drawPosX - 10,          // X - padding
        (float)drawPosY - 5,           // Y - padding
        (float)textWidth + 20,         // Lebar + padding ganda
        (float)textHeight + 10         // Tinggi + padding ganda
    };
}


void ShowOptions(float *volume, bool *isFullscreen) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int selectedOption = 0; // 0: Volume, 1: Fullscreen, 2: Back

    const int totalOptions = 3;
    Rectangle optionHitboxes[totalOptions];
    Rectangle volumeDecreaseRect, volumeIncreaseRect;

    // Inisialisasi elemen UI bersama
    // Ini akan mengatur ulang animasi seperti fade-in, posisi mobil, dll.
    InitUIElements(screenWidth, screenHeight);

    // Menggunakan isInMainMenu dari header.h atau global state jika diperlukan untuk musik
    if (isInMainMenu && !IsMusicStreamPlaying(menuBacksound)) {
        PlayMenuBacksound(); // Atau musik spesifik untuk layar opsi
    }

    while (!WindowShouldClose()) {
        // Update musik jika ada
        UpdateMusicStream(menuBacksound);

        // Perbarui animasi UI bersama
        UpdateUIElements(screenWidth, screenHeight);
        float currentGlobalAlpha = GetUIGlobalAlpha();

        Vector2 mousePos = GetMousePosition();

        // --- Logika Input ---

        // Navigasi Keyboard (sudah ada)
        if (IsKeyPressed(KEY_DOWN)) {
            selectedOption = (selectedOption + 1) % totalOptions;
            menusound(); // Jika ada suara navigasi
        }
        if (IsKeyPressed(KEY_UP)) {
            selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;
            menusound(); // Jika ada suara navigasi
        }

        // Logika Mouse Hover & Click untuk Opsi Utama
        for (int i = 0; i < totalOptions; i++) {
            if (CheckCollisionPointRec(mousePos, optionHitboxes[i])) {
                if (selectedOption != i) {
                     selectedOption = i;
                     menusound(); // Suara saat hover jika berbeda dari suara navigasi keyboard
                }
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    // Aksi berdasarkan selectedOption yang di-klik
                    if (selectedOption == 1) { // Fullscreen
                        *isFullscreen = !(*isFullscreen);
                        if (*isFullscreen) {
                            if (!IsWindowFullscreen()) ToggleFullscreen();
                        } else {
                            if (IsWindowFullscreen()) ToggleFullscreen();
                        }
                        // menusound_confirm(); // Suara konfirmasi
                    } else if (selectedOption == 2) { // Back
                        // menusound_cancel(); // Suara batal/kembali
                        return;
                    }
                    // Untuk Volume (selectedOption == 0), klik pada label utama tidak melakukan apa-apa
                    // karena ada tombol < > terpisah
                }
            }
        }

        // Logika Volume (Keyboard & Mouse)
        bool volumeChangedByKeyboard = false;
        if (selectedOption == 0) { // Jika "Volume" dipilih oleh keyboard
            if (IsKeyDown(KEY_LEFT)) {
                if (*volume > 0.0f) *volume -= 0.01f;
                volumeChangedByKeyboard = true;
            }
            if (IsKeyDown(KEY_RIGHT)) {
                if (*volume < 1.0f) *volume += 0.01f;
                volumeChangedByKeyboard = true;
            }
        }

        // Mouse untuk tombol Volume Decrease "<"
        if (CheckCollisionPointRec(mousePos, volumeDecreaseRect)) {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { // Terus menerus jika ditahan
                 if (*volume > 0.0f) *volume -= (IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 0.015f : 0.05f); // Lebih cepat jika ditahan
                 // menusound_tick(); // Suara tick volume
            }
        }
        // Mouse untuk tombol Volume Increase ">"
        if (CheckCollisionPointRec(mousePos, volumeIncreaseRect)) {
             if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                 if (*volume < 1.0f) *volume += (IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 0.015f : 0.05f);
                 // menusound_tick();
            }
        }

        // Batasi nilai volume dan terapkan
        if (*volume < 0.0f) *volume = 0.0f;
        if (*volume > 1.0f) *volume = 1.0f;
        SetMasterVolume(*volume); // Terapkan perubahan volume
        if (volumeChangedByKeyboard) {
            // menusound_tick(); // Suara tick jika diubah keyboard
        }


        // Aksi Tombol Enter (Keyboard)
        if (IsKeyPressed(KEY_ENTER)) {
            // menusound_confirm();
            if (selectedOption == 1) { // Fullscreen
                *isFullscreen = !(*isFullscreen);
                 if (*isFullscreen) {
                    if (!IsWindowFullscreen()) ToggleFullscreen();
                } else {
                    if (IsWindowFullscreen()) ToggleFullscreen();
                }
            } else if (selectedOption == 2) { // Back
                return;
            }
            // Untuk Volume (selectedOption == 0), Enter tidak melakukan apa-apa di sini
        }

        // --- Proses Menggambar ---
        BeginDrawing();
            ClearBackground(BLACK); // Latar belakang dasar, akan ditimpa oleh DrawSharedUILayout

            // Gambar UI Bersama (latar belakang, mobil, judul, dll.)
            // Judul: "Options", Subjudul: NULL (tidak ada), Ayam: false (tidak digambar)
            DrawSharedUILayout(screenWidth, screenHeight, "Options", NULL, false);

            // Gambar Opsi Spesifik Layar Ini
            int Y_start = screenHeight / 2 - 50; // Posisi Y awal untuk opsi
            int Y_spacing = 60; // Jarak antar opsi
            int optionFontSize = 25;
            int valueFontSize = 25;
            int arrowFontSize = 30;

            // 1. Opsi Volume
            char volumeText[32];
            sprintf(volumeText, "Volume: %d%%", (int)(*volume * 100));
            bool isVolumeSelected = (selectedOption == 0);
            
            // Hitbox untuk label "Volume" (untuk seleksi keyboard/mouse hover)
            optionHitboxes[0] = DrawOptionItem(
                "Volume", 
                screenWidth / 2, // Sedikit ke kiri dari nilai
                Y_start, 
                optionFontSize, 
                isVolumeSelected, 
                currentGlobalAlpha,
                GAME_LIGHT, GAME_YELLOW
            );

            // Tombol "<" untuk mengurangi volume
            volumeDecreaseRect = DrawOptionItem("<", screenWidth / 2 - 60, Y_start + Y_spacing/2 + 5, arrowFontSize, CheckCollisionPointRec(mousePos, volumeDecreaseRect), currentGlobalAlpha, GAME_BLUE, GAME_YELLOW);
            // Teks nilai volume
            DrawText(TextFormat("%d%%", (int)(*volume*100)), screenWidth/2 - MeasureText("100%", valueFontSize)/2, Y_start + Y_spacing/2 + 5 - valueFontSize/2, valueFontSize, ColorAlpha(GAME_LIGHT, currentGlobalAlpha));
            // Tombol ">" untuk menambah volume
            volumeIncreaseRect = DrawOptionItem(">", screenWidth / 2 + 60, Y_start + Y_spacing/2 + 5, arrowFontSize, CheckCollisionPointRec(mousePos, volumeIncreaseRect), currentGlobalAlpha, GAME_BLUE, GAME_YELLOW);


            // 2. Opsi Fullscreen
            char fullscreenText[32];
            sprintf(fullscreenText, "Fullscreen: %s", *isFullscreen ? "ON" : "OFF");
            optionHitboxes[1] = DrawOptionItem(
                fullscreenText, 
                screenWidth / 2, 
                Y_start + Y_spacing * 1 + 20, // Beri sedikit ruang lebih setelah volume
                optionFontSize, 
                selectedOption == 1, 
                currentGlobalAlpha,
                GAME_LIGHT, GAME_YELLOW
            );

            // 3. Opsi Kembali (Back)
            optionHitboxes[2] = DrawOptionItem(
                "Back", 
                screenWidth / 2, 
                Y_start + Y_spacing * 2 + 20, 
                optionFontSize, 
                selectedOption == 2, 
                currentGlobalAlpha,
                GAME_LIGHT, GAME_YELLOW
            );

            // Gambar Teks Hak Cipta
            DrawCopyright(screenWidth, screenHeight);

        EndDrawing();
    }
}