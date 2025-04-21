#include "LibraryFaiz.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "../GLOBALHEADER.h"
#include "../azzam/LibraryAzzam.h"

void DrawCenteredText(const char *text, int fontSize, Color color)
{
    int textWidth = MeasureText(text, fontSize); // Mengukur lebar teks
    int x = (SCREEN_WIDTH - textWidth) / 2;      // Posisi X agar teks di tengah
    int y = SCREEN_HEIGHT / 2 - fontSize / 2;    // Posisi Y agar teks di tengah

    DrawText(text, x, y, fontSize, color);
}

void DrawGame(Camera2D camera)
{
    BeginDrawing();
    ClearBackground(WHITE);
    BeginMode2D(camera);

    sprintf(coordText, "Coordinate: %2d,%2d", player.x, player.y);
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

    if (PermainanBerakhir)
    {
        if (!kalah)
        {
            DrawCenteredText("MENANG", 40, RED);
        }
    }

    if (!gameStarted)
    {
    DrawCenteredText("Use arrow keys to move", 30, BLACK);
    }

    EndMode2D();
    EndDrawing();
} // 101, 59

void UpdateCarMovement()
{
    frameCounter++;
    if (frameCounter >= CAR_MOVE_DELAY)
    {
        for (int i = 0; i < numCars; i++)
        {
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

            // Hitung jarak antara mobil dan pemain
            Vector2 playerPos = {player.x * CELL_SIZE, player.y * CELL_SIZE};
            Vector2 carPos = {cars[i].x * CELL_SIZE, cars[i].y * CELL_SIZE};
            float distance = CalculateDistance(playerPos, carPos);

            // Atur volume berdasarkan jarak (semakin dekat, semakin keras)
            float maxDistance = 500.0f;
            float volume = 1.0f - (distance / maxDistance);
            if (volume < 0.0f)
                volume = 0.0f;
            SetSoundVolume(carSound, volume);

            if (!IsSoundPlaying(carSound))
            {
                PlaySound(carSound);
            }
        }
        frameCounter = 0;
    }
}

void InitGrid()
{
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            if ((i == 166 && j == 23) || (i == 39 && j == 53))
            {
                grid[i][j] = CHECKPOINT_LINE; // Garis biru setiap 50 baris
            } // else if (i % 8 == 0) {
              // grid[i][j] = LANE_MARK; // Garis putih tiap 8 baris

            else if ((i == 131 && j == 51) || (i == 53 && j == 37))
            {
                grid[i][j] = HEALTH_UP; // Garis biru setiap 50 baris
            }
            else if ((i == 151 && j == 29) || (i == 21 && j == 55))
            {
                grid[i][j] = POINTS;
            }
            else
            {
                grid[i][j] = ROAD; // Jalan normal
            }
            // grid [209][j] = LANE_MARK;
            // grid [203][j] = LANE_MARK;
            // grid [199][j] = LANE_MARK;
            // grid [187][j] = LANE_MARK;
        }
    }
}

void checkposition(Player *player)
{
    
    if (player->y % 50 == 0 && lastScorePosition != player->y && player->y < 200) 
    {
        player->score += 2 * comboMultiplier; 
        lastScorePosition = player->y; 
        comboStreak++; 
        
       
        if (comboStreak % 3 == 0) 
        {
            comboMultiplier++;
        }
    }

    if (grid[player->y][player->x] == CHECKPOINT_LINE)
    {
        passed = true;
        checkpoint.x = player->x;
        checkpoint.y = player->y;
        player->score += 10 * comboMultiplier; 

        grid[player->y][player->x] = ROAD;
    }
    else if (grid[player->y][player->x] == HEALTH_UP)
    {
        ++player->lives;
        grid[player->y][player->x] = ROAD;
    }
    else if (grid[player->y][player->x] == POINTS)
    {
        player->score += 10 * comboMultiplier; 
        grid[player->y][player->x] = ROAD;
    }
}


void InitGame()
{
    srand(time(NULL));

    kalah = false;
    PermainanBerakhir = false;
    player.score = 0;
    player.lives = MAX_LIVES;  
    numCars = NUM_CARS_START; 
    carSpeed = CAR_SPEED_START;
    level = 1;             

    player.x = GRID_WIDTH / 2;
    player.y = GRID_HEIGHT - 2;
    checkpoint.x = player.x;
    checkpoint.y = player.y;

    printf("Game di-reset: lives = %d, score = %d, posisi = (%d, %d)\n",
           player.lives, player.score, player.x, player.y);

    InitGrid();
    printf("Grid berhasil di-reset\n");
    
    int array[24] = {9, 14, 27, 32, 49, 55, 61, 67, 95, 101, 115, 121, 127, 133, 139, 145, 151, 157, 175, 181, 187, 193, 205, 211};
    int directray[24] = {-1, -1, 1, 1, -1, -1, 1, 1, /**/ 1, /**/ -1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, 1};

    InitGrid(); // Pastikan grid diinisialisasi sebelum menempatkan mobil

    for (int i = 0; i < numCars; i++)
    {
        int col;

        col = rand() % (GRID_WIDTH - GRID_START);
        int direction = directray[i];

        cars[i] = (Car){col, array[i], carSpeed, direction};
        cars[i].type = (rand() % 4), (rand() % 4), (rand() % 4); // Pilih jenis mobil secara acak
    }

    camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
    camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.7f;


}

void ResetCombo()
{
    comboMultiplier = 1;
    comboStreak = 0;
}

void CheckCollision()
{
    for (int i = 0; i < numCars; i++)
    {
        if (cars[i].direction == 1)
        {
            if (((player.x <= cars[i].x + 7) && (player.x >= cars[i].x - 2.3)) && ((player.y <= cars[i].y + 2.7) && (player.y >= cars[i].y - 2)))
            {
                PlaySound(nabrak);

                player.x = checkpoint.x;
                player.y = checkpoint.y;
                player.lives--;
                if (player.lives <= 0)
                {
                    kalah = true;
                }
                break;
            }
        }
        else
        {
            if (((player.x <= cars[i].x - 3) && (player.x >= cars[i].x - 9.3)) && ((player.y <= cars[i].y + 2.7) && (player.y >= cars[i].y - 2)))
            {
                PlaySound(nabrak);

                player.x = checkpoint.x;
                player.y = checkpoint.y;
                player.lives--;
                if (player.lives <= 0)
                {
                    kalah = true;
                }
                break;
            }
        }
    }
}


void UpdateGame(Camera2D *camera) {

    if (!gameStarted) 
    {
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) 
        {
            gameStarted = true; // Mulai permainan saat tombol pertama ditekan
        }
        return; // Jangan update posisi player sebelum permainan dimulai
    }
    
    if (!PermainanBerakhir) {
        UpdateCarMovement();

        if (IsKeyPressed(KEY_UP))
            movement[0] = true;
        if (IsKeyPressed(KEY_DOWN))
            movement[1] = true;
        if (IsKeyPressed(KEY_LEFT))
            movement[2] = true;
        if (IsKeyPressed(KEY_RIGHT))
            movement[3] = true;

        if (movement[0])
        {
            player.y -= PLAYER_SPEED + 1;
            movement[0] = false;
        }
        if (movement[1])
        {
            player.y += PLAYER_SPEED + 1;
            movement[1] = false;
        }
        if (movement[2])
        {
            player.x -= PLAYER_SPEED + 1;
            movement[2] = false;
        }
        if (movement[3])
        {
            player.x += PLAYER_SPEED + 1;
            movement[3] = false;
        }

        checkposition(&player);
        CheckCollision();
    }

    if (player.y == 0)
    {
        NextLevel(camera, &player);
    }
}

float CalculateDistance(Vector2 pos1, Vector2 pos2)
{
    return sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
}