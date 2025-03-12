#include "raylib.h"
#include "GLOBALHEADER.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "LibraryAndrew.c"
#include "HeaderAndrew.h"

Player player;
vector checkpoint;
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
    
    for (int i = 0; i < numCars; i++) {
        int lane = rand() % (GRID_HEIGHT - 2);
        int col = rand() % GRID_WIDTH;
        int direction = (rand() % 2) ? 1 : -1;
        cars[i] = (Car){col, lane, carSpeed, direction};
        cars[i].type = rand() % 3;  // Assigns 0, 1, or 2 randomly
    }
}

void NextLevel() {
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
    
    InitGame();
}

void UpdateGame() {
    if (!PermainanBerakhir) {
        frameCounter++;
        if (frameCounter >= CAR_MOVE_DELAY) {
            for (int i = 0; i < numCars; i++) {
                int newX = cars[i].x + cars[i].direction * cars[i].speed;
                if (newX < 0) newX = GRID_WIDTH - 1;
                if (newX >= GRID_WIDTH) newX = 0;
                cars[i].x = newX;
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
        NextLevel();
    }
}

void DrawGame(Camera2D camera) {
    

    BeginDrawing();
    ClearBackground(WHITE);

    BeginMode2D(camera);

    sprintf(coordText, "X: %d, Y: %d", player.x, player.y);

    RenderGrid();
    // Menggambar elemen game dalam dunia (terpengaruh oleh kamera)
    
    RenderRoads(SCREEN_WIDTH, SCREEN_HEIGHT);

    RenderCars(&numCars, cars);

    RenderCharacter(&PlayerSprite, player);

    EndMode2D(); // Selesai menggambar elemen dalam dunia

    // Menggambar elemen UI/HUD (agar tetap di layar)
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
    // Menampilkan menu
    MenuOption selectedMenu = ShowMenu();

    if (selectedMenu == MENU_EXIT) {
        CloseWindow();
        return 0;
    }

    InitGame();
    LoadAllTextures();

    camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
    camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.5f;

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