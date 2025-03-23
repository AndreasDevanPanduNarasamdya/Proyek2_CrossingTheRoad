#include "LibraryFaiz.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "GLOBALHEADER.h"


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
                //for (int x = j - 3; x < j+3; x++)
                //{
                    grid[i][j] = CHECKPOINT_LINE; // Garis biru setiap 50 baris
                //}
            }
            else if ((i == 131 && j == 51) || (i == 53 && j == 37)) {// Add to the linked list
                grid[i][j] = HEALTH_UP; // Garis biru setiap 50 baris
            }
            else if ((i == 53 && j == 21) || (i == 153 && j == 39)) {
                grid[i][j] = POINTS;
            }
            else {
                grid[i][j] = ROAD;  //Jalan normal
            }

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
        for (int x = player->x - 3; x < player->x+3; x++)
                {
                    grid[player->y][player->x] = ROAD; // Garis biru setiap 50 baris
                }
    }
    if (grid[player->y][player->x] == HEALTH_UP) 
    {
        //health_upgrade = true;
        ++player->lives;

        // Tandai checkpoint sudah dilewati agar tidak terus menambah skor
        grid[player->y][player->x] = ROAD;
    }
    if (grid[player->y][player->x] == POINTS) 
    {
        player->score += 10;
        grid[player->y][player->x] = ROAD;

        // Tandai checkpoint sudah dilewati agar tidak terus menambah skor
        
    }
}



void InitGame() {
    srand(time(NULL));  // Initialize random number generator once per function call

    player.x = GRID_WIDTH / 2;
    player.y = GRID_HEIGHT;
    checkpoint.x = player.x;
    checkpoint.y = player.y;
    player.score = 0;
    player.lives = MAX_LIVES;

    int array[53];  // Declare array based on the maximum possible size across all levels
    int directray[53];  // Declare directray based on the maximum possible size across all levels

    // Initialize array and directray based on the current level
    if (level == 3) {
        int level1_array[] = {9, 14, 27, 32, 49, 55, 61, 67, 78, 95, 101, 115, 121, 127, 133, 139, 145, 151, 157, 175, 181, 187, 193, 205, 211};
        int level1_directray[] = {-1, -1, 1, 1, -1, -1, 1, 1, -1,  1, -1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, 1};
        
        // Copy level-specific arrays to global arrays
        memcpy(array, level1_array, sizeof(level1_array));
        memcpy(directray, level1_directray, sizeof(level1_directray));
    }
    else if (level == 1) {
        int level2_array[] = {15, 18, 30, 38, 46, 55, 61, 64, 76, 89, 95, 110, 117, 122, 129, 135, 138, 146, 155, 163, 166, 172, 181, 182, 192, 205, 204, 206, 220, 230, 247, 249, 252, 258, 267, 273, 276, 282, 295, 298};
        int level2_directray[] = {-1,-1, 1, 1, 1, -1, -1, 1, 1, -1, -1, 1, -1, 1,-1,-1,1,1,-1-1,1,1,-1-1,1,1, -1, 1, 1, -1, -1, -1, 1, 1, -1, -1, 1, 1, -1, 1};
        
        memcpy(array, level2_array, sizeof(level2_array));
        memcpy(directray, level2_directray, sizeof(level2_directray));
    }
    else if (level == 3) {
        int level3_array[] = {9, 12, 15, 30, 38, 46, 52, 58, 64, 76, 88, 96, 110, 114, 122, 126, 134, 140, 144, 150, 160, 166, 170, 178, 184, 192, 202, 208, 218, 226, 238, 244, 250, 256, 262, 268, 274, 280, 286, 294, 300, 106, 312, 318, 324, 330, 336, 342, 348, 354, 360, 366, 372};
        int level3_directray[] = { -1, -1, -1, 1, -1, 1, 1, -1, 1, 1, -1, 1, 1, -1, -1, -1, 1, -1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, 1, 1, 1, -1, 1, 1, -1, -1, -1, 1, -1, 1, 1, -1};
        
        memcpy(array, level3_array, sizeof(level3_array));
        memcpy(directray, level3_directray, sizeof(level3_directray));
    }

    InitGrid();  // Ensure the grid is initialized before placing cars

    // Initialize the cars
    for (int i = 0; i < numCars; i++) {
        int col = rand() % (GRID_WIDTH - GRID_START);
        int direction = directray[i];

        // Set car properties
        cars[i] = (Car){col, array[i], carSpeed, direction};

        // Assign a random type to the car (0, 1, 2, or 3)
        cars[i].type = rand() % 4;
    }
}


void NextLevel() {
    PermainanBerakhir = (level == 2);
    if (!PermainanBerakhir) {
        level++;
        numCars += 5;  // Increase the number of cars at each level
        carSpeed = (carSpeed < 5) ? carSpeed + 1 : 5;  // Increase car speed, but limit it to 5
        player.x = GRID_WIDTH / 2;
        player.y = GRID_HEIGHT - 2;
        
        checkpoint.x = player.x;
        checkpoint.y = player.y;
        
        InitGame();  // Reinitialize the game for the next level
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

        if (player.x < 15) player.x = 15;
        if (player.x >= GRID_WIDTH-17) player.x = GRID_WIDTH - 17;
        if (player.y < 0) player.y = 0;
        if (player.y >= GRID_HEIGHT) player.y = GRID_HEIGHT - 1;

        checkposition(&player);

        CheckCollision();
    }

    if (player.y == 0) {
        NextLevel();
    }
}