#include "LibraryFaiz.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "GLOBALHEADER.h"


void InitGrid() {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (i % 50 == 0) {
                grid[i][j] = CHECKPOINT_LINE; // Garis biru setiap 50 baris
            } else if (i % 8 == 0) {
                grid[i][j] = LANE_MARK; // Garis putih tiap 8 baris
            } else {
                grid[i][j] = ROAD; // Jalan normal
            }
        }
    }
}


void checkposition(Player *player) {
    if (grid[player->y][player->x] == CHECKPOINT_LINE && player->y != ScorTerakhir) {
        checkpoint.x = player->x; 
        checkpoint.y = player->y;
        player->score += 10;
        
        ScorTerakhir = player->y;

        // Tandai checkpoint sudah dilewati agar tidak terus menambah skor
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



void UpdateGame() {
    if (!PermainanBerakhir) {
        frameCounter++;
        if (frameCounter >= CAR_MOVE_DELAY) {
            for (int i = 0; i < numCars; i++) {
                int newX = cars[i].x + cars[i].direction * cars[i].speed;
                if (newX < 0) newX = GRID_WIDTH - 1;
                if (newX >= GRID_WIDTH) newX = 0;
                grid[cars[i].y][cars[i].x] = ROAD;
                cars[i].x = newX;
                grid[cars[i].y][cars[i].x] = CAR;
            }
            frameCounter = 0;
        }

        if (IsKeyPressed(KEY_UP)) movement[0] = true;
        if (IsKeyPressed(KEY_DOWN)) movement[1] = true;
        if (IsKeyPressed(KEY_LEFT)) movement[2] = true;
        if (IsKeyPressed(KEY_RIGHT)) movement[3] = true;

        if (movement[0]) { player.y -= PLAYER_SPEED; movement[0] = false; }
        if (movement[1]) { player.y += PLAYER_SPEED; movement[1] = false; }
        if (movement[2]) { player.x -= PLAYER_SPEED; movement[2] = false; }
        if (movement[3]) { player.x += PLAYER_SPEED; movement[3] = false; }

        if (player.x < 0) player.x = 0;
        if (player.x >= GRID_WIDTH) player.x = GRID_WIDTH - 1;
        if (player.y < 0) player.y = 0;
        if (player.y >= GRID_HEIGHT) player.y = GRID_HEIGHT - 1;

        checkposition(&player);

        for (int i = 0; i < numCars; i++) {
            if (player.x == cars[i].x && player.y == cars[i].y) {
                player.x = checkpoint.x;
                player.y = checkpoint.y;
                player.lives--;
                if (player.lives <= 0) {
                    kalah = true;
                }
                break;
            }
        }
    }

    if (player.y == 0) {
        NextLevel();
    }
}
