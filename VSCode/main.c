#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 1000   // 100 cells per layar
#define SCREEN_HEIGHT 1000  // 100 cells per layar
#define CELL_SIZE 10
#define GRID_WIDTH 100   // 100 cells per layar
#define GRID_HEIGHT 200  // 200 cells ke atas
#define PLAYER_SIZE 10
#define CAR_WIDTH 20
#define CAR_HEIGHT 10
#define NUM_CARS 50
#define PLAYER_SPEED 1   // Kecepatan pemain 1 pixel per detik
#define CAR_SPEED 2      // Kecepatan mobil 6 pixel per detik
#define CAR_MOVE_DELAY 4  // 10 frame = 6 pixel per detik dengan 60 FPS

#define GRASS_COLOR DARKGREEN
#define TREE_COLOR DARKBROWN
#define LANE_COLOR DARKGRAY

typedef enum { EMPTY, PLAYER, CAR } CellType;

typedef struct {
    int x, y;
    int speed;
    int direction;
} Car;

typedef struct {
    int x, y;
} Player;

CellType grid[GRID_HEIGHT][GRID_WIDTH];
Player player;
Car cars[NUM_CARS];
int frameCounter = 0;  // Untuk memperlambat pergerakan mobil

void InitGame() {
    srand(time(NULL));

    // Inisialisasi grid kosong
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            grid[i][j] = EMPTY;
        }
    }

    // Inisialisasi pemain
    player.x = GRID_WIDTH / 2;
    player.y = GRID_HEIGHT - 2;
    grid[player.y][player.x] = PLAYER;

    // Inisialisasi mobil
    for (int i = 0; i < NUM_CARS; i++) {
        int lane = rand() % (GRID_HEIGHT - 2);
        int col = rand() % GRID_WIDTH;
        int direction = (rand() % 2) ? 1 : -1;

        cars[i] = (Car){col, lane, CAR_SPEED, direction};
        grid[lane][col] = CAR;
    }
}

void UpdateGame() {
    frameCounter++;  // Hitung waktu untuk pergerakan mobil

    // Pergerakan mobil setiap 10 frame (6 pixel per detik)
    if (frameCounter >= CAR_MOVE_DELAY) {
        for (int i = 0; i < NUM_CARS; i++) {
            int newX = cars[i].x + cars[i].direction * cars[i].speed;

            if (newX < 0) newX = GRID_WIDTH - 1;
            if (newX >= GRID_WIDTH) newX = 0;

            cars[i].x = newX;
        }

        frameCounter = 0;  // Reset counter
    }

    // Pergerakan pemain
    int newX = player.x, newY = player.y;

    // Pemain bergerak 1 pixel per tekanan tombol
    if (IsKeyPressed(KEY_UP)) newY -= PLAYER_SPEED;
    if (IsKeyPressed(KEY_DOWN)) newY += PLAYER_SPEED;
    if (IsKeyPressed(KEY_LEFT)) newX -= PLAYER_SPEED;
    if (IsKeyPressed(KEY_RIGHT)) newX += PLAYER_SPEED;

    // Pastikan pemain tidak keluar layar
    if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT) {
        player.x = newX;
        player.y = newY;
    }
}

void DrawGame(Camera2D camera) {
    BeginDrawing();
    ClearBackground(BLACK);  // Background hitam
    
    BeginMode2D(camera);

    // Gambar Rerumputan pada awal dan akhir map
    for (int i = 0; i < GRID_WIDTH; i++) {
        DrawRectangle(i * CELL_SIZE, 0, CELL_SIZE, CELL_SIZE, GRASS_COLOR);  // Rerumputan di atas
        DrawRectangle(i * CELL_SIZE, (GRID_HEIGHT - 1) * CELL_SIZE, CELL_SIZE, CELL_SIZE, GRASS_COLOR);  // Rerumputan di bawah
    }

    // Gambar Pohon di sepanjang jalan
    for (int i = 0; i < NUM_CARS; i++) {
        if (rand() % 10 == 0) {
            int treeX = rand() % GRID_WIDTH;
            int treeY = rand() % GRID_HEIGHT;
            DrawRectangle(treeX * CELL_SIZE, treeY * CELL_SIZE, 15, 15, TREE_COLOR);  // Pohon kecil
        }
    }

    // Gambar Lanes/Jalur Jalan
    for (int i = 0; i < GRID_HEIGHT; i++) {
        if (i % 10 == 0) {  // Setiap 10 cell, buat jalur
            for (int j = 0; j < GRID_WIDTH; j++) {
                DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, LANE_COLOR);
            }
        }
    }

    // Gambar Mobil
    for (int i = 0; i < NUM_CARS; i++) {
        int x = cars[i].x * CELL_SIZE;
        int y = cars[i].y * CELL_SIZE;

        // Badan mobil
        DrawRectangle(x, y, CAR_WIDTH, CAR_HEIGHT, RED);
        
        // Roda mobil (atas & bawah)
        DrawRectangle(x + 2, y - 2, 5, 4, BLACK);  // Roda atas
        DrawRectangle(x + 2, y + CAR_HEIGHT - 2, 5, 4, BLACK);  // Roda bawah
    }

    // Gambar Pemain
    DrawRectangle(player.x * CELL_SIZE, player.y * CELL_SIZE, PLAYER_SIZE, PLAYER_SIZE, BLUE);
    
    // Teks Instruksi
    DrawText("Use Arrow Keys to Move", 20, 20, 20, LIGHTGRAY);

    EndMode2D();
    EndDrawing();
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crossing Highway Grid");
    SetTargetFPS(60);
    InitGame();

    Camera2D camera = {0};
    camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
    camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) {
        UpdateGame();

        // Kamera mengikuti pemain
        camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};

        DrawGame(camera);
    }

    CloseWindow();
    return 0;
}
