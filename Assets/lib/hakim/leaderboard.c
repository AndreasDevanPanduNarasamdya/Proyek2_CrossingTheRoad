#include "../header.h"

LeaderboardEntry leaderboardEntries[MAX_LEADERBOARD_ENTRIES];
int numLeaderboardEntries = 0;


// Fungsi yang akan menampilkan layar untuk input nama pemain dan mengisi nameBuffer.
void InputPlayerName(char *nameBuffer, int maxLength) {
    int letterCount = 0;
    // Inisialisasi nameBuffer dengan string kosong.
    nameBuffer[0] = '\0';

    // UNtuk menentukan posisi dan ukuran kotak input nama.
    Rectangle textBox = {
        SCREEN_WIDTH / 2 - 150,
        SCREEN_HEIGHT / 2 - 30,
        300,
        60
    };

    bool mouseOnText = false;
    int framesCounter = 0;

    // Loop utama untuk layar input nama.
    while (!WindowShouldClose()) {
        if (CheckCollisionPointRec(GetMousePosition(), textBox)) {
            mouseOnText = true;
        } else {
            mouseOnText = false;
        }

        if (mouseOnText) {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
            int key = GetCharPressed(); // Dapatkan karakter yang ditekan (unicode)

            while (key > 0) {
                if (((key >= 32) && (key <= 125)) && (letterCount < maxLength - 1)) {
                    nameBuffer[letterCount] = (char)key;
                    letterCount++;
                    nameBuffer[letterCount] = '\0'; // Pastikan null-terminated
                }
                key = GetCharPressed(); // Cek karakter lain di frame yang sama
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                nameBuffer[letterCount] = '\0';
            }
        } else {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }

        if (mouseOnText) framesCounter++;
        else framesCounter = 0;

        // Selesai input jika Enter ditekan DAN nama sudah diisi.
        if (IsKeyPressed(KEY_ENTER) && (letterCount > 0)) {
            return; // Keluar dari fungsi
        }

        if (IsKeyPressed(KEY_Q)) {
            if (letterCount == 0) {
                strcpy(nameBuffer, "Player");
            }
            return; 
        }

        BeginDrawing();
        ClearBackground(RAYWHITE); 

        DrawText("Enter Your Name:",
                 SCREEN_WIDTH / 2 - MeasureText("Enter Your Name:", 30) / 2,
                 textBox.y - 70, // Posisi teks instruksi
                 30, DARKGRAY);

        DrawRectangleRec(textBox, LIGHTGRAY);
        if (mouseOnText) DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
        else DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);

        DrawText(nameBuffer, (int)textBox.x + 10, (int)textBox.y + (textBox.height / 2) - 20, 40, MAROON);

        DrawText(TextFormat("Karakter: %d / %d", letterCount, maxLength - 1),
                 textBox.x, textBox.y + textBox.height + 10, 20, DARKGRAY);

        if (mouseOnText && (letterCount < maxLength - 1)) {
            if (((framesCounter / 20) % 2) == 0) { // Kursor berkedip
                DrawText("_", (int)textBox.x + 10 + MeasureText(nameBuffer, 40), (int)textBox.y + (textBox.height / 2) - 15, 40, MAROON);
            }
        }
        
        DrawText("Tekan ENTER untuk Simpan, Q untuk Batal",
                 SCREEN_WIDTH / 2 - MeasureText("Tekan ENTER untuk Simpan, ESC untuk Batal", 20) / 2,
                 SCREEN_HEIGHT - 60, 20, GRAY);
        EndDrawing();
    }
}


// Fungsi pembanding untuk qsort (urutkan skor dari tertinggi ke terendah)
int compareLeaderboardEntries(const void *a, const void *b) {
    LeaderboardEntry *entryA = (LeaderboardEntry *)a;
    LeaderboardEntry *entryB = (LeaderboardEntry *)b;

    // Urutkan descending berdasarkan skor
    if (entryB->score > entryA->score) return 1;
    if (entryB->score < entryA->score) return -1;
    
    return 0;
}

void SaveScoreToLeaderboard(const char *playerName, int score) {

    if (numLeaderboardEntries == MAX_LEADERBOARD_ENTRIES && score <= leaderboardEntries[MAX_LEADERBOARD_ENTRIES - 1].score) {

        printf("Skor %d oleh %s tidak cukup tinggi untuk masuk leaderboard penuh.\n", score, playerName);
        return;
    }

    int targetIndex;

    if (numLeaderboardEntries < MAX_LEADERBOARD_ENTRIES) {
        // Leaderboard belum penuh, skor baru langsung ditambahkan di akhir (untuk sementara)
        targetIndex = numLeaderboardEntries;
        numLeaderboardEntries++; // Jumlah entri bertambah
    } else {

        targetIndex = MAX_LEADERBOARD_ENTRIES - 1;
    }

    // Salin nama dan skor ke posisi target
    strncpy(leaderboardEntries[targetIndex].name, playerName, MAX_PLAYER_NAME_LENGTH - 1);
    leaderboardEntries[targetIndex].name[MAX_PLAYER_NAME_LENGTH - 1] = '\0'; // Pastikan null-terminated
    leaderboardEntries[targetIndex].score = score;

    // Urutkan kembali seluruh array leaderboard setelah penambahan/penggantian
    qsort(leaderboardEntries, numLeaderboardEntries, sizeof(LeaderboardEntry), compareLeaderboardEntries);

    printf("Skor %d untuk %s berhasil diproses untuk leaderboard (in-memory).\n", score, playerName);

    // Nantinya, setelah baris ini, Anda akan memanggil SaveLeaderboardToFile().
}


void ShowLeaderboardScreen(void) {
    printf("DEBUG: ShowLeaderboardScreen - FUNGSI DIMASUKI.\n"); // <--- DEBUG POINT

    InitUIElements(SCREEN_WIDTH, SCREEN_HEIGHT);

    int screenFrameCounter = 0; 

    while (!WindowShouldClose()) {
        // 1. Update Logika UI Animasi Latar Belakang
        UpdateUIElements(SCREEN_WIDTH, SCREEN_HEIGHT);
        float currentGlobalAlpha = GetUIGlobalAlpha(); // Dapatkan alpha saat ini untuk elemen UI

        // Cek input untuk keluar dari layar leaderboard
        if ( IsKeyPressed(KEY_Q)) {
            printf("DEBUG: ShowLeaderboardScreen - Tombol keluar (Enter/Q) ditekan pada frame ke-%d.\n", screenFrameCounter); // <--- DEBUG POINT

            break; 
        }

        BeginDrawing();

        // 2. Gambar Latar Belakang dan Elemen UI Bersama

        DrawSharedUILayout(SCREEN_WIDTH, SCREEN_HEIGHT, "LEADERBOARD", NULL, false);
        
        // 3. Tampilkan Entri Leaderboard 
        if (numLeaderboardEntries == 0) {
            DrawText("Leaderboard masih kosong!",
                     SCREEN_WIDTH / 2 - MeasureText("Leaderboard masih kosong!", 20) / 2,
                     SCREEN_HEIGHT / 2 + 20, // Sesuaikan Y agar tidak tertimpa judul dari DrawSharedUILayout
                     20, 
                     ColorAlpha(RAYWHITE, currentGlobalAlpha)); // Gunakan global alpha
        } else {
            // Untuk menyesuaikan entri pertama
            int leaderboardStartY = SCREEN_HEIGHT / 4 + 60; // Perkiraan posisi Y awal

            for (int i = 0; i < numLeaderboardEntries; i++) {
                char entryText[256];
                sprintf(entryText, "%2d. %-*s %5d",
                        i + 1,
                        MAX_PLAYER_NAME_LENGTH + 2,
                        leaderboardEntries[i].name,
                        leaderboardEntries[i].score);
                
                int textWidth = MeasureText(entryText, 20);
                int posX = SCREEN_WIDTH / 2 - textWidth / 2;

                DrawText(entryText,
                         posX,
                         leaderboardStartY + i * 35, // Jarak vertikal antar entri
                         20,
                         ColorAlpha(RAYWHITE, currentGlobalAlpha)); 
            }
        }

        // 4. Gambar Instruksi untuk Kembali 
        const char* backInstruction = "Tekan Q untuk Kembali";
        DrawText(backInstruction,
                 SCREEN_WIDTH / 2 - MeasureText(backInstruction, 20) / 2,
                 SCREEN_HEIGHT - 70,
                 20, 
                 ColorAlpha(LIGHTGRAY, currentGlobalAlpha)); 


        EndDrawing();
    }
    printf("DEBUG: ShowLeaderboardScreen - FUNGSI SELESAI setelah %d frame.\n", screenFrameCounter); // <--- DEBUG POINT

}



void LoadLeaderboardFromFile(const char *filename) {
    FILE *file = fopen(filename, "r"); // Buka file dalam mode baca ("r")

    numLeaderboardEntries = 0; // Selalu reset jumlah entri saat memuat dari file

    if (file == NULL) {
        TraceLog(LOG_WARNING, "File skor '%s' tidak ditemukan. Leaderboard dimulai kosong.", filename);
        return; // Keluar jika file tidak ada
    }

    TraceLog(LOG_INFO, "Membaca leaderboard dari file '%s'...", filename);

    char lineBuffer[256]; // Buffer untuk membaca satu baris dari file
    char sscanf_format_string[50]; // Buffer untuk string format sscanf dinamis

    // Membuat format string seperti "%15[^,],%d" secara dinamis
    // Jika MAX_PLAYER_NAME_LENGTH adalah 16, maka MAX_PLAYER_NAME_LENGTH - 1 adalah 15.
    // Format untuk sprintf: "%%<lebar_nama>[^,],%%d"
    sprintf(sscanf_format_string, "%%%d[^,],%%d", MAX_PLAYER_NAME_LENGTH - 1);
    // Contoh: Jika MAX_PLAYER_NAME_LENGTH = 16, sscanf_format_string akan berisi "%15[^,],%d"

    // Baca baris per baris sampai akhir file atau sampai leaderboard penuh
    while (fgets(lineBuffer, sizeof(lineBuffer), file) != NULL && numLeaderboardEntries < MAX_LEADERBOARD_ENTRIES) {
        // Coba parsing baris menggunakan format string yang sudah dibuat
        if (sscanf(lineBuffer, sscanf_format_string,
                   leaderboardEntries[numLeaderboardEntries].name,
                   &leaderboardEntries[numLeaderboardEntries].score) == 2) {
            
            // Pastikan nama diakhiri dengan null-terminator, ini penting!
            leaderboardEntries[numLeaderboardEntries].name[MAX_PLAYER_NAME_LENGTH - 1] = '\0';
            
            numLeaderboardEntries++; // Tambah jumlah entri yang berhasil dimuat
        } else {
            // Jika sscanf gagal mem-parsing 2 item, mungkin barisnya tidak sesuai format atau kosong.
            // Hapus newline di akhir lineBuffer untuk logging yang lebih bersih jika ada.
            lineBuffer[strcspn(lineBuffer, "\r\n")] = 0;
            if (strlen(lineBuffer) > 0) { // Hanya log jika baris tidak benar-benar kosong
                TraceLog(LOG_WARNING, "Baris tidak valid atau format salah di file skor: '%s'", lineBuffer);
            }
        }
    }

    fclose(file); // Tutup file setelah selesai membaca

    // Setelah memuat, PENTING untuk mengurutkan data leaderboard
    if (numLeaderboardEntries > 0) {
        // Pastikan fungsi compareLeaderboardEntries sudah benar untuk urutan descending
        qsort(leaderboardEntries, numLeaderboardEntries, sizeof(LeaderboardEntry), compareLeaderboardEntries);
        TraceLog(LOG_INFO, "Leaderboard berhasil dimuat dan diurutkan. Jumlah entri: %d", numLeaderboardEntries);
    } else {
        TraceLog(LOG_INFO, "Leaderboard kosong setelah mencoba memuat dari file (atau file kosong).");
    }
}