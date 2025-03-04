#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define CELL_SIZE 10
#define GRID_WIDTH 100
#define GRID_HEIGHT 200
#define PLAYER_SIZE 10
#define CAR_WIDTH 20
#define CAR_HEIGHT 10
#define NUM_CARS_START 20
#define PLAYER_SPEED 1
#define CAR_SPEED_START 1
#define CAR_MOVE_DELAY 6
#define LANE_COLOR DARKGRAY
#define MAX_LIVES 3
#define CELL_EMPTY 0
#define CELL_ROAD 1
#define CELL_CHECKPOINT 2
#define CAMERA_SPEED 1
#define CAMERA_DISTANCE 50
#define INACTIVE_TIME_LIMIT 180
#define CAMERA_DEATH_DISTANCE 300
#define CELL_CAR 3

typedef enum {
    VEHICLE_CAR,
    VEHICLE_TRUCK,
    VEHICLE_BUS,
    VEHICLE_BIKE
} VehicleType;

typedef struct {
    int x, y;
    int speed;
    int direction;
    VehicleType type;
} Car;

typedef struct {
    int x, y, score, lives;
} Player;

typedef struct vector {
    int x, y;
} vector;

Player player;
vector checkpoint;
Camera2D camera = {0};
Car cars[NUM_CARS_START * 2];
int frameCounter = 0;
int ScorTerakhir = -1;
bool PermainanBerakhir = false;
bool kalah = false;
int level = 1;
int numCars = NUM_CARS_START;
int carSpeed = CAR_SPEED_START;
bool movement[4] = {false, false, false, false};
int map[GRID_HEIGHT][GRID_WIDTH];
int inactiveTimer = 0;

void DrawVehicle(Car car) {
    int x = car.x * CELL_SIZE;
    int y = car.y * CELL_SIZE;

    switch (car.type) {
        case VEHICLE_CAR:
            DrawRectangle(x, y, CAR_WIDTH, CAR_HEIGHT, RED); // Mobil kecil
            DrawRectangle(x + 2, y - 2, 5, 4, BLACK); // Lampu depan
            DrawRectangle(x + 2, y + CAR_HEIGHT - 2, 5, 4, BLACK); // Lampu belakang
            break;

        case VEHICLE_TRUCK:
            DrawRectangle(x, y, CAR_WIDTH * 2, CAR_HEIGHT, BLUE); // Truk
            DrawRectangle(x + 4, y - 2, 5, 4, BLACK); // Lampu depan
            DrawRectangle(x + 4, y + CAR_HEIGHT - 2, 5, 4, BLACK); // Lampu belakang
            break;

        case VEHICLE_BUS:
            DrawRectangle(x, y, CAR_WIDTH * 3, CAR_HEIGHT, YELLOW); // Bus
            DrawRectangle(x + 6, y - 2, 5, 4, BLACK); // Lampu depan
            DrawRectangle(x + 6, y + CAR_HEIGHT - 2, 5, 4, BLACK); // Lampu belakang
            break;

        case VEHICLE_BIKE:
            DrawRectangle(x, y, CAR_WIDTH / 2, CAR_HEIGHT, GREEN); // Sepeda motor
            DrawRectangle(x + 1, y - 2, 3, 4, BLACK); // Lampu depan
            DrawRectangle(x + 1, y + CAR_HEIGHT - 2, 3, 4, BLACK); // Lampu belakang
            break;
    }
}

void GenerateMap() {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (y % 8 == 0) {
                map[y][x] = CELL_ROAD;  // Jalur mobil
            } else if (y % 50 == 0) {
                map[y][x] = CELL_CHECKPOINT;  // Checkpoint pemain
            } else {
                map[y][x] = CELL_EMPTY;  // Area kosong
            }
        }
    }
}

void checkposition(Player *player, vector *check) {
    if (player->y % 50 == 0 && player->y != ScorTerakhir) {
        check->x = player->x;
        check->y = player->y;
        player->score += 10;
        ScorTerakhir = player->y;
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

    GenerateMap();

    // Inisialisasi kendaraan dengan jenis yang berbeda
    for (int i = 0; i < numCars; i++) {
        int x, y;
        do {
            x = rand() % GRID_WIDTH;
            y = rand() % GRID_HEIGHT;
        } while (map[y][x] != CELL_EMPTY || x == 0 || x == GRID_WIDTH - 1); // Pastikan kendaraan hanya ditempatkan di sel kosong dan tidak di tepi grid

        VehicleType type = rand() % 4; // Pilih jenis kendaraan secara acak
        int direction = (rand() % 2) ? 1 : -1;
        int speed = carSpeed;

        // Sesuaikan kecepatan berdasarkan jenis kendaraan
        switch (type) {
            case VEHICLE_CAR: speed = carSpeed; break;
            case VEHICLE_TRUCK: speed = (carSpeed - 1 > 0) ? carSpeed - 1 : 1; break; // Truk lebih lambat, minimal kecepatan 1
            case VEHICLE_BUS: speed = carSpeed; break;
            case VEHICLE_BIKE: speed = carSpeed + 1; break; // Sepeda motor lebih cepat
        }

        cars[i] = (Car){x, y, speed, direction, type};
        map[y][x] = CELL_CAR;
    }
}

void NextLevel(Camera2D *camera) {
    PermainanBerakhir = false;
    if (level == 2) PermainanBerakhir = true;
    level++;
    numCars += 5;
    carSpeed++;
    if (carSpeed > 5) carSpeed = 5;
    player.x = GRID_WIDTH / 2;
    player.y = GRID_HEIGHT - 2;
    checkpoint.x = player.x;
    checkpoint.y = player.y;
    camera->target.y = player.y * CELL_SIZE;

    InitGame();
}

void UpdateGame() {
    if (!PermainanBerakhir) {
        frameCounter++;
        if (frameCounter >= CAR_MOVE_DELAY) {
            for (int i = 0; i < numCars; i++) {
                int newX = cars[i].x + cars[i].direction * cars[i].speed;

                // Cek apakah sel baru valid dan kosong
                if (newX >= 0 && newX < GRID_WIDTH && map[cars[i].y][newX] == CELL_EMPTY) {
                    // Hapus mobil dari posisi lama
                    map[cars[i].y][cars[i].x] = CELL_EMPTY;
                    // Pindahkan mobil ke posisi baru
                    cars[i].x = newX;
                    map[cars[i].y][cars[i].x] = CELL_CAR;
                } else {
                    // Jika tidak, balik arah mobil
                    cars[i].direction *= -1;
                    // Coba bergerak ke arah yang berlawanan
                    newX = cars[i].x + cars[i].direction * cars[i].speed;
                    if (newX >= 0 && newX < GRID_WIDTH && map[cars[i].y][newX] == CELL_EMPTY) {
                        map[cars[i].y][cars[i].x] = CELL_EMPTY;
                        cars[i].x = newX;
                        map[cars[i].y][cars[i].x] = CELL_CAR;
                    }
                }
            }
            frameCounter = 0;
        }

        bool playerMoved = false;
        if (IsKeyPressed(KEY_UP)) { player.y -= PLAYER_SPEED; playerMoved = true; }
        if (IsKeyPressed(KEY_DOWN)) { player.y += PLAYER_SPEED; playerMoved = true; }
        if (IsKeyPressed(KEY_LEFT)) { player.x -= PLAYER_SPEED; playerMoved = true; }
        if (IsKeyPressed(KEY_RIGHT)) { player.x += PLAYER_SPEED; playerMoved = true; }

        if (player.x < 0) player.x = 0;
        if (player.x >= GRID_WIDTH) player.x = GRID_WIDTH - 1;
        if (player.y < 0) player.y = 0;
        if (player.y >= GRID_HEIGHT) player.y = GRID_HEIGHT - 1;

        if (playerMoved) {
            inactiveTimer = 0;
        } else {
            inactiveTimer++;
        }

        if (inactiveTimer >= INACTIVE_TIME_LIMIT) {
            kalah = true;
        }

        checkposition(&player, &checkpoint);

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
        NextLevel(&camera);
    }
}

void DrawGame(Camera2D camera) {
    BeginDrawing();
    ClearBackground(WHITE);
    BeginMode2D(camera);

    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (map[y][x] == CELL_ROAD) {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, LANE_COLOR);
            } else if (map[y][x] == CELL_CHECKPOINT) {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLUE);
            }
        }
    }

    for (int i = 0; i < numCars; i++) {
        DrawVehicle(cars[i]);
    }

    DrawRectangle(player.x * CELL_SIZE, player.y * CELL_SIZE, PLAYER_SIZE, PLAYER_SIZE, GRAY);
    DrawText(TextFormat("Score: %d", player.score), player.x * CELL_SIZE - 400, player.y * CELL_SIZE - 400, 20, DARKGRAY);
    DrawText(TextFormat("Lives: %d", player.lives), player.x * CELL_SIZE - 400, player.y * CELL_SIZE - 350, 20, DARKGRAY);
    DrawText(TextFormat("Level: %d", level), player.x * CELL_SIZE - 400, player.y * CELL_SIZE - 300, 20, DARKGRAY);
    DrawText("Use Arrow Keys to Move", 10, 100, 20, DARKGRAY);

    if (PermainanBerakhir) {
        DrawText("MENANG", player.x * CELL_SIZE, player.y * CELL_SIZE, 40, RED);
    }

    if (kalah) {
        DrawText("GAME OVER", player.x * CELL_SIZE, player.y * CELL_SIZE, 40, RED);
        PermainanBerakhir = true;
    }

    EndMode2D();
    EndDrawing();
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crossing Highway Grid");
    SetTargetFPS(60);
    InitGame();

    camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
    camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) {
        UpdateGame();

        if (!kalah && !PermainanBerakhir) {
            camera.target.y -= CAMERA_SPEED; // Kamera selalu bergerak ke depan

            // Cek jika pemain tertinggal terlalu jauh
            if (player.y * CELL_SIZE > camera.target.y + CAMERA_DEATH_DISTANCE) {
                kalah = true;
            }
        }

        DrawGame(camera);
    }

    CloseWindow();
    return 0;
}