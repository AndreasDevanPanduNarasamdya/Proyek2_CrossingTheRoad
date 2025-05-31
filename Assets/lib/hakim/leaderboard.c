#include "../header.h"

// Head pointer untuk linked list
LeaderboardNode* leaderboardHead = NULL;
int numLeaderboardEntries = 0;

// Fungsi untuk membuat node baru
LeaderboardNode* createLeaderboardNode(const char* name, int score) {
    LeaderboardNode* newNode = (LeaderboardNode*)malloc(sizeof(LeaderboardNode));
    if (newNode == NULL) {
        printf("Error: Gagal mengalokasikan memori untuk node leaderboard\n");
        return NULL;
    }
    
    strncpy(newNode->name, name, MAX_PLAYER_NAME_LENGTH - 1);
    newNode->name[MAX_PLAYER_NAME_LENGTH - 1] = '\0';
    newNode->score = score;
    newNode->next = NULL;
    
    return newNode;
}

// Fungsi untuk menambah skor ke leaderboard (sorted insertion)
void SaveScoreToLeaderboard(const char* playerName, int score) {
    printf("DEBUG: Menambahkan skor %d untuk pemain %s ke leaderboard\n", score, playerName);
    
    LeaderboardNode* newNode = createLeaderboardNode(playerName, score);
    if (newNode == NULL) {
        return;
    }
    
    if (leaderboardHead == NULL || score > leaderboardHead->score) {
        newNode->next = leaderboardHead;
        leaderboardHead = newNode;
        numLeaderboardEntries++;

        if (numLeaderboardEntries > MAX_LEADERBOARD_ENTRIES) {
            LeaderboardNode* current = leaderboardHead;
            LeaderboardNode* prev = NULL;
            while (current->next != NULL) {
                prev = current;
                current = current->next;
            }
            if (prev != NULL) {
                prev->next = NULL;
                free(current);
                numLeaderboardEntries--;
            }
        }

        printf("Skor %d untuk %s berhasil ditambahkan ke leaderboard\n", score, playerName);
        SaveLeaderboardToFile("leaderboard.txt");  // <--- Tambahan
        return;
    }

    LeaderboardNode* current = leaderboardHead;
    LeaderboardNode* prev = NULL;
    int position = 1;

    while (current != NULL && current->score >= score) {
        prev = current;
        current = current->next;
        position++;
    }

    if (position > MAX_LEADERBOARD_ENTRIES) {
        printf("Skor %d oleh %s tidak cukup tinggi untuk masuk leaderboard\n", score, playerName);
        free(newNode);
        return;
    }

    newNode->next = current;
    if (prev != NULL) {
        prev->next = newNode;
    }

    numLeaderboardEntries++;

    if (numLeaderboardEntries > MAX_LEADERBOARD_ENTRIES) {
        current = leaderboardHead;
        prev = NULL;
        while (current->next != NULL) {
            prev = current;
            current = current->next;
        }
        if (prev != NULL) {
            prev->next = NULL;
            free(current);
            numLeaderboardEntries--;
        }
    }

    printf("Skor %d untuk %s berhasil ditambahkan ke leaderboard pada posisi %d\n", score, playerName, position);

    SaveLeaderboardToFile("leaderboard.txt"); 
}


// Fungsi untuk menyimpan leaderboard ke file
void SaveLeaderboardToFile(const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Gagal membuka file %s untuk menulis\n", filename);
        return;
    }
    
    LeaderboardNode* current = leaderboardHead;
    int count = 0;
    
    while (current != NULL && count < MAX_LEADERBOARD_ENTRIES) {
        fprintf(file, "%s,%d\n", current->name, current->score);
        current = current->next;
        count++;
    }
    
    fclose(file);
    printf("Leaderboard berhasil disimpan ke file %s (%d entri)\n", filename, count);
}

// Fungsi untuk memuat leaderboard dari file
void LoadLeaderboardFromFile(const char* filename) {
    // Bersihkan leaderboard yang ada
    ClearLeaderboard();
    
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("File %s tidak ditemukan. Memulai dengan leaderboard kosong.\n", filename);
        return;
    }
    
    char lineBuffer[256];
    char name[MAX_PLAYER_NAME_LENGTH];
    int score;
    
    printf("Memuat leaderboard dari file %s...\n", filename);
    
    while (fgets(lineBuffer, sizeof(lineBuffer), file) != NULL) {
        // Parse baris dengan format "nama,skor"
        if (sscanf(lineBuffer, "%15[^,],%d", name, &score) == 2) {
            LeaderboardNode* newNode = createLeaderboardNode(name, score);
            if (newNode != NULL) {
                // Insert di akhir list (file sudah terurut)
                if (leaderboardHead == NULL) {
                    leaderboardHead = newNode;
                } else {
                    LeaderboardNode* current = leaderboardHead;
                    while (current->next != NULL) {
                        current = current->next;
                    }
                    current->next = newNode;
                }
                numLeaderboardEntries++;
            }
        } else {
            // Hapus newline untuk logging yang bersih
            lineBuffer[strcspn(lineBuffer, "\r\n")] = 0;
            if (strlen(lineBuffer) > 0) {
                printf("Warning: Format baris tidak valid: '%s'\n", lineBuffer);
            }
        }
    }
    
    fclose(file);
    printf("Leaderboard berhasil dimuat: %d entri\n", numLeaderboardEntries);
}

// Fungsi untuk membersihkan semua node dalam linked list
void ClearLeaderboard(void) {
    LeaderboardNode* current = leaderboardHead;
    LeaderboardNode* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    leaderboardHead = NULL;
    numLeaderboardEntries = 0;
    printf("Leaderboard telah dibersihkan\n");
}

// Fungsi untuk menampilkan layar leaderboard
void ShowLeaderboardScreen(void) {
    printf("DEBUG: ShowLeaderboardScreen - FUNGSI DIMASUKI.\n");
    
    InitUIElements(SCREEN_WIDTH, SCREEN_HEIGHT);
    int screenFrameCounter = 0;
    
    while (!WindowShouldClose()) {
        UpdateUIElements(SCREEN_WIDTH, SCREEN_HEIGHT);
        float currentGlobalAlpha = GetUIGlobalAlpha();
        
        // Input untuk keluar
        if (IsKeyPressed(KEY_Q)) {
            printf("DEBUG: ShowLeaderboardScreen - Tombol keluar (Q) ditekan pada frame ke-%d.\n", screenFrameCounter);
            break;
        }
        
        BeginDrawing();
        
        // Gambar latar belakang dan UI
        DrawSharedUILayout(SCREEN_WIDTH, SCREEN_HEIGHT, "LEADERBOARD", NULL, false);
        
        // Tampilkan entri leaderboard
        if (numLeaderboardEntries == 0) {
            DrawText("Leaderboard masih kosong!",
                     SCREEN_WIDTH / 2 - MeasureText("Leaderboard masih kosong!", 20) / 2,
                     SCREEN_HEIGHT / 2 + 20,
                     20,
                     ColorAlpha(RAYWHITE, currentGlobalAlpha));
        } else {
            int leaderboardStartY = SCREEN_HEIGHT / 4 + 60;
            LeaderboardNode* current = leaderboardHead;
            int rank = 1;
            
            while (current != NULL && rank <= MAX_LEADERBOARD_ENTRIES) {
                char entryText[256];
                sprintf(entryText, "%2d. %-*s %5d",
                        rank,
                        MAX_PLAYER_NAME_LENGTH + 2,
                        current->name,
                        current->score);
                
                int textWidth = MeasureText(entryText, 20);
                int posX = SCREEN_WIDTH / 2 - textWidth / 2;
                
                DrawText(entryText,
                         posX,
                         leaderboardStartY + (rank - 1) * 35,
                         20,
                         ColorAlpha(RAYWHITE, currentGlobalAlpha));
                
                current = current->next;
                rank++;
            }
        }
        
        // Instruksi kembali
        const char* backInstruction = "Tekan Q untuk Kembali";
        DrawText(backInstruction,
                 SCREEN_WIDTH / 2 - MeasureText(backInstruction, 20) / 2,
                 SCREEN_HEIGHT - 70,
                 20,
                 ColorAlpha(LIGHTGRAY, currentGlobalAlpha));
        
        EndDrawing();
        screenFrameCounter++;
    }
    
    printf("DEBUG: ShowLeaderboardScreen - FUNGSI SELESAI setelah %d frame.\n", screenFrameCounter);
}

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
                 SCREEN_WIDTH / 2 - MeasureText("Tekan ENTER untuk Simpan, Q untuk Batal", 20) / 2,
                 SCREEN_HEIGHT - 60, 20, GRAY);
        EndDrawing();
    }
}

const char *GetUsernameInput() {
    static char username[100] = "";
    int letterCount = 0;
    bool enterPressed = false;

    SetExitKey(KEY_NULL);

    while (!enterPressed && !WindowShouldClose()) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (letterCount < 20)) {
                username[letterCount++] = (char)key;
                username[letterCount] = '\0';
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0) {
            letterCount--;
            username[letterCount] = '\0';
        }

        if (IsKeyPressed(KEY_ENTER) && letterCount > 0) {
            enterPressed = true;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawSharedUILayout(SCREEN_WIDTH, SCREEN_HEIGHT, "LEADERBOARD", NULL, false);
        DrawText("Masukkan Username:", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 100, 30, BLACK);
        DrawRectangle(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 50, 300, 50, LIGHTGRAY);
        DrawText(username, SCREEN_WIDTH / 2 - 145, SCREEN_HEIGHT / 2 - 45, 30, DARKBLUE);
        DrawText("Tekan ENTER untuk lanjut", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 20, 20, GRAY);
        EndDrawing();
    }

    SetExitKey(KEY_ESCAPE);
    return username;
}
