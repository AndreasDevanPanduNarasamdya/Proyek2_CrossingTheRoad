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

typedef struct {
    int x, y;
    int speed;
    int direction;
} Car;

typedef struct {
    int x, y, score, lives;
} Player;

typedef struct vector {
    int x, y;
} vector;

Player player;
vector checkpoint;
Car cars[NUM_CARS_START * 2];
int frameCounter = 0;
int ScorTerakhir = -1;
bool PermainanBerakhir = false;
bool kalah = false;
int level = 1;
int numCars = NUM_CARS_START;
int carSpeed = CAR_SPEED_START;

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

        int newX = player.x, newY = player.y;
        if (IsKeyPressed(KEY_UP)) newY -= PLAYER_SPEED;
        if (IsKeyPressed(KEY_DOWN)) newY += PLAYER_SPEED;
        if (IsKeyPressed(KEY_LEFT)) newX -= PLAYER_SPEED;
        if (IsKeyPressed(KEY_RIGHT)) newX += PLAYER_SPEED;

        if (newX >= 0 && newX < GRID_WIDTH && newY >= 0 && newY < GRID_HEIGHT) {
            player.x = newX;
            player.y = newY;
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
        NextLevel();
    }
}

void DrawGame(Camera2D camera) {
    BeginDrawing();
    ClearBackground(WHITE);
    BeginMode2D(camera);

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

    for (int i = 0; i < numCars; i++) {
        int x = cars[i].x * CELL_SIZE;
        int y = cars[i].y * CELL_SIZE;
        DrawRectangle(x, y, CAR_WIDTH, CAR_HEIGHT, RED);
        DrawRectangle(x + 2, y - 2, 5, 4, BLACK);
        DrawRectangle(x + 2, y + CAR_HEIGHT - 2, 5, 4, BLACK);
    }

    DrawRectangle(player.x * CELL_SIZE, player.y * CELL_SIZE, PLAYER_SIZE, PLAYER_SIZE, GRAY);
    DrawText(TextFormat("Score: %d", player.score), player.x *CELL_SIZE - 400, player.y * CELL_SIZE - 400, 20, DARKGRAY);
    DrawText(TextFormat("Lives: %d", player.lives),  player.x *CELL_SIZE - 400, player.y * CELL_SIZE - 350, 20, DARKGRAY);
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

    Camera2D camera = {0};
    camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
    camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) {
            UpdateGame();
            camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
            DrawGame(camera);    
    }

    CloseWindow();
    return 0;
}