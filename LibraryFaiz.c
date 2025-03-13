#include "LibraryFaiz.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "GLOBALHEADER.h"

void RenderGrid() {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            Color cellColor = WHITE; // Default warna jalan biasa

            if (grid[i][j] == LANE_MARK) {
                cellColor = LANE_COLOR; // Warna garis jalur
            } 
            else if (grid[i][j] == CHECKPOINT_LINE) {
                cellColor = BLUE; // Warna garis checkpoint
            }
            DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, cellColor);
        }
    }
}


void UpdateCarMovement() {
    for (int i = 0; i < numCars; i++) {
        // Update posisi mobil langsung berdasarkan kecepatan dan arah
        cars[i].x += cars[i].direction * cars[i].speed;

        // Jika mobil keluar dari batas layar, kembalikan ke sisi lain
        if (cars[i].x < 0) {
            cars[i].x = SCREEN_WIDTH;  // Muncul kembali di sisi kanan
        }
        if (cars[i].x > SCREEN_WIDTH) {
            cars[i].x = 0;  // Muncul kembali di sisi kiri
        }
    }
}


void InitGrid() {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (i >= 300 && i < 310) {
                grid[i][j] = CHECKPOINT_LINE; // Mengosongkan area di antara 100-110
            }  else if (i % 18 == 0) {
                grid[i][j] = LANE_MARK; // Garis hita, tiap 18 baris
            } else if (i % 9 == 0) {
                grid[i][j] = putihs; // Jalan normal
            } else if(i == 305) {
                grid[i][j] = check;
            } else{
                grid[i][j] = ROAD;
            }
        }
    }
}



void checkposition(Player *player) {
    if (grid[player->y][player->x] == check && player->y != ScorTerakhir) {
        checkpoint.x = player->x; 
        checkpoint.y = player->y;
        
        comboStreak++;
        if (comboStreak >= comboThreshold) {
            comboMultiplier++;
            comboStreak = 0; // Reset streak setelah naik level multiplier
        }
        
        player->score += 10 * comboMultiplier; // Gunakan multiplier untuk skor
        ScorTerakhir = player->y;
        grid[player->y][player->x] = ROAD;
    }
}


void InitGame() {
    srand(time(NULL));
    player.x = GRID_WIDTH / 2;
    player.y = GRID_HEIGHT - 2;
    checkpoint.x = player.x;
    checkpoint.y = player.y;
    player.score = 0;
    player.lives = MAX_LIVES;
    
    InitGrid();  // Pastikan grid diinisialisasi sebelum menempatkan mobil

    for (int i = 0; i < numCars; i++) {
        int lane, col;

        do {
            lane = rand() % (GRID_HEIGHT - 2);
        } while (grid[lane][0] == LANE_MARK);  // Pastikan bukan garis batas

        col = rand() % GRID_WIDTH;
        int direction = (rand() % 2) ? 1 : -1;

        cars[i] = (Car){col, lane, carSpeed, direction};
        cars[i].type = rand() % 3;  // Pilih jenis mobil secara acak
    }
}


void NextLevel() {
    PermainanBerakhir = (level == 2);
    if (!PermainanBerakhir) {
        level++;
        numCars += 5;
        carSpeed = (carSpeed < 5) ? carSpeed + 1 : 5;
        player.x = GRID_WIDTH / 2;
        player.y = GRID_HEIGHT - 2;
        
        checkpoint.x = player.x;
        checkpoint.y = player.y;
        InitGame();
    }
}

void ResetCombo() {
    comboMultiplier = 1;
    comboStreak = 0;
}


void CheckCollision() {
    for (int i = 0; i < numCars; i++) {
        if (player.x + 4 == cars[i].x  && player.y == cars[i].y) {
            player.x = checkpoint.x;
            player.y = checkpoint.y;
            player.lives--;
            ResetCombo(); // Reset combo jika tertabrak
            if (player.lives <= 0) {
                kalah = true;
            }
            break;
        }
    }
}

void UpdateGame() {
    if (!PermainanBerakhir) {
        
        UpdateCarMovement();

        if (IsKeyPressed(KEY_UP)) movement[0] = true;
        if (IsKeyPressed(KEY_DOWN)) movement[1] = true;
        if (IsKeyPressed(KEY_LEFT)) movement[2] = true;
        if (IsKeyPressed(KEY_RIGHT)) movement[3] = true;

        if (movement[0]) { player.y -= PLAYER_SPEED+1; movement[0] = false; }
        if (movement[1]) { player.y += PLAYER_SPEED+1; movement[1] = false; }
        if (movement[2]) { player.x -= PLAYER_SPEED+1; movement[2] = false; }
        if (movement[3]) { player.x += PLAYER_SPEED+1; movement[3] = false; }

        if (player.x < 0) player.x = 0;
        if (player.x >= GRID_WIDTH) player.x = GRID_WIDTH - 1;
        if (player.y < 0) player.y = 0;
        if (player.y >= GRID_HEIGHT) player.y = GRID_HEIGHT - 1;

        checkposition(&player);

        CheckCollision();
    }

    if (player.y == 0) {
        NextLevel();
    }
}
