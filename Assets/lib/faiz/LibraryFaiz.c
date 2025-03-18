#include "LibraryFaiz.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "../GLOBALHEADER.h"
#include "../azzam/LibraryAzzam.h"


void RenderGrid() {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            Color cellColor = DARKGRAY; // Default warna jalan biasa

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

void DrawGame(Camera2D camera) {
    BeginDrawing();
    ClearBackground(WHITE);
    BeginMode2D(camera);

    sprintf(coordText, "Coordinate: %2d,%2d", player.x, player.y);
    // Menggambar elemen game dalam dunia (terpengaruh oleh kamera)
    RenderRoads(SCREEN_WIDTH, SCREEN_HEIGHT);

    RenderCars(&numCars, cars);

    RenderFlags();

    RenderHealths();

    RenderPoints();
    
    RenderCharacter(&PlayerSprite, player);
     // Selesai menggambar elemen dalam dunia
    EndMode2D();

    RenderInstructions(player, coordText, level);

    ResetTimer();
    if (PermainanBerakhir) {
        DrawText("MENANG", player.x * CELL_SIZE, player.y * CELL_SIZE, 40, RED);
    }

    if (kalah) {
        DrawText("GAME OVER", player.x * CELL_SIZE, player.y * CELL_SIZE, 40, RED);
        PermainanBerakhir = true;
    }
    
    EndMode2D();
    EndDrawing();
}//101, 59

void UpdateCarMovement() {
    frameCounter++;
    if (frameCounter >= CAR_MOVE_DELAY) {
        for (int i = 0; i < numCars; i++) {
            int newX = cars[i].x + cars[i].direction * cars[i].speed;
            if (newX < 0) 
            {
               newX = GRID_WIDTH - 1;
            }
            if (newX >= GRID_WIDTH) 
            {
                newX = 0;
            }
            grid[cars[i].y][cars[i].x] = ROAD;
            cars[i].x = newX;
            grid[cars[i].y][cars[i].x] = CAR;
        }
        frameCounter = 0;
    }
}


void InitGrid() {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if ((i == 165 && j == 23) || (i == 39 && j == 53)) {
                grid[i][j] = CHECKPOINT_LINE; // Garis biru setiap 50 baris
            } //else if (i % 8 == 0) {
                //grid[i][j] = LANE_MARK; // Garis putih tiap 8 baris
    
            else if ((i == 131 && j == 51) || (i == 53 && j == 37)) {
                grid[i][j] = HEALTH_UP; // Garis biru setiap 50 baris
            }
            else if ((i == 151 && j == 29) || (i == 21 && j == 55)) {
                grid[i][j] = POINTS;
            }
            else {
                grid[i][j] = ROAD;  //Jalan normal
            }
            //grid [209][j] = LANE_MARK;
            //grid [203][j] = LANE_MARK;
            //grid [199][j] = LANE_MARK;
            //grid [187][j] = LANE_MARK;
        }
    }
}



void checkposition(Player *player) {
    if (grid[player->y][player->x] == CHECKPOINT_LINE) 
    {
        passed = true;
        checkpoint.x = player->x; 
        checkpoint.y = player->y;
        player->score += 10;
        ScorTerakhir = player->y;

        // Tandai checkpoint sudah dilewati agar tidak terus menambah skor
        grid[player->y][player->x] = ROAD;
    }
    else if (grid[player->y][player->x] == HEALTH_UP) 
    {
        ++player->lives;
        
        // Tandai checkpoint sudah dilewati agar tidak terus menambah skor
        grid[player->y][player->x] = ROAD;
    }
    else if (grid[player->y][player->x] == POINTS) 
    {
        player->score += 10;
        
        // Tandai checkpoint sudah dilewati agar tidak terus menambah skor
        grid[player->y][player->x] = ROAD;
    } 
}



void InitGame() {
    srand(time(NULL));
    player.x = GRID_WIDTH / 2;
    player.y = GRID_HEIGHT;
    checkpoint.x = player.x;
    checkpoint.y = player.y;
    player.score = 0;
    player.lives = MAX_LIVES;
    int array[24] = {9, 14, 27, 32, 49, 55, 61, 67, 95, 101, 115, 121, 127, 133, 139, 145, 151, 157, 175, 181, 187, 193, 205, 211};
    int directray[24] = {-1, -1, 1, 1, -1, -1, 1, 1,/**/ 1, /**/-1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, 1 };
    
    InitGrid();  // Pastikan grid diinisialisasi sebelum menempatkan mobil

    for (int i = 0; i < numCars; i++) {
         int  col;

      

        col = rand() % (GRID_WIDTH - GRID_START);
        int direction = directray[i];

        cars[i] = (Car){col, array[i], carSpeed, direction};
        cars[i].type = (rand() % 4), (rand() % 4), (rand() % 4);  // Pilih jenis mobil secara acak
    }
}


void ResetCombo() {
    comboMultiplier = 1;
    comboStreak = 0;
}


void CheckCollision() {
    for (int i = 0; i < numCars; i++) {
        if (cars[i].direction == 1)
        {
            if (((player.x <= cars[i].x+7) && (player.x >= cars[i].x-2.3)) && ((player.y <= cars[i].y+2.7) && (player.y >= cars[i].y-2))) {
            player.x = checkpoint.x;
            player.y = checkpoint.y;
            player.lives--;
            if (player.lives <= 0) {
                kalah = true;
            }
            break;
            }
        }
        else
        {
            if (((player.x <= cars[i].x-3) && (player.x >= cars[i].x-9.3)) && ((player.y <= cars[i].y+2.7) && (player.y >= cars[i].y-2))) {
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
}


void UpdateGame(Camera2D *camera) {
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
        NextLevel(camera,&player);
    }
}
