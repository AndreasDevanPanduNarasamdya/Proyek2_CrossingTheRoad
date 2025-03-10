#include "raylib.h"
#include "GLOBALHEADER.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "LibraryAndrew.c"
#include "HeaderAndrew.h"

Player player;
vector checkpoint;
Camera2D camera = {0};
Car cars[NUM_CARS_START * 2];
Camera2D camera = {0};
int frameCounter = 0;
int ScorTerakhir = -1;
bool PermainanBerakhir = false;
bool kalah = false;
int level = 1;
int numCars = NUM_CARS_START;
int carSpeed = CAR_SPEED_START;
bool movement[4] = {false,false,false,false};
char coordText[50];

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
        cars[i].type = rand() % 3;  // Assigns 0, 1, or 2 randomly
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

                if (newX >= 0 && newX < GRID_WIDTH && map[cars[i].y][newX] == CELL_EMPTY) {
                    map[cars[i].y][cars[i].x] = CELL_EMPTY;
                    cars[i].x = newX;
                    map[cars[i].y][cars[i].x] = CELL_CAR;
                } else {
                    cars[i].direction *= -1;
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

        // Cek tabrakan dengan semua kendaraan
        for (int i = 0; i < numCars; i++) {
            if (player.x == cars[i].x && player.y == cars[i].y) {
                player.lives--; // Kurangi nyawa
                if (player.lives <= 0) {
                    kalah = true;
                } else {
                    // Reset pemain ke checkpoint jika masih punya nyawa
                    player.x = checkpoint.x;
                    player.y = checkpoint.y;
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

    sprintf(coordText, "X: %d, Y: %d", player.x, player.y);

    RenderRoads(SCREEN_WIDTH, SCREEN_HEIGHT);

    for (int i = 0; i < GRID_HEIGHT; i++) {
        if (i % 8 == 0) {
            for (int j = 0; j < GRID_WIDTH; j++) {
                DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, LANE_COLOR);
            }
        } else if (i % 50 == 0) {
            for (int n = 0; n < GRID_WIDTH; n++) {
                DrawRectangle(n * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLUE);
            }
        }
    }

    RenderCars(&numCars, cars);

    RenderCharacter(&PlayerSprite, player);
    RenderInstructions(player, coordText, level);

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
    LoadAllTextures();

    camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
    camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) {
        UpdateGame();

        if (!kalah && !PermainanBerakhir) {
            camera.target.y -= CAMERA_SPEED ; // Kamera selalu bergerak ke depan

            // Cek jika pemain tertinggal terlalu jauh
            if (player.y * CELL_SIZE > camera.target.y + CAMERA_DEATH_DISTANCE) {
                kalah = true;
            }
        }

        DrawGame(camera);
    }

    UnloadAllTextures();
    CloseWindow();
    return 0;
}