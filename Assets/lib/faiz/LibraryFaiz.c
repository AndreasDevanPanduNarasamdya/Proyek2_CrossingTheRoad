#include "LibraryFaiz.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "../GLOBALHEADER.h"
#include "../azzam/LibraryAzzam.h"

void CreateEmpty(Carlist *L) {
    L->First = NULL;
}

address Alokasi(Car carData) {
    address P = (address)malloc(sizeof(ElmtList));
    if (P != NULL) {
        P->info = carData;
        P->next = NULL;
    }
    return P;
}

void InsertFirst(Carlist *L, Car carData) {
    address P = Alokasi(carData);
    if (P != NULL) {
        P->next = L->First;
        L->First = P;
    }
}

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
    // Menggambar elemen game dalam dunia (terpengaruh oleh kamera)
    RenderRoads(SCREEN_WIDTH, SCREEN_HEIGHT);

    RenderCars(&carList);

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

void UpdateCarMovement() {
    frameCounter++;
    if (frameCounter >= CAR_MOVE_DELAY) {
        address curr = carList.First;
        while (curr != NULL) {
            Car *c = &curr->info;

            int newX = c->x + c->direction * c->speed;
            if (newX < 0) newX = GRID_WIDTH - 1;
            if (newX >= GRID_WIDTH) newX = 0;

            grid[c->y][c->x] = ROAD;
            c->x = newX;
            grid[c->y][c->x] = CAR;

            // Kurangi timer cooldown setiap frame
            carSoundCooldown -= GetFrameTime(); // GetFrameTime() = waktu antar frame (dari raylib)

            if (carSoundCooldown <= 0.0f) {
             Vector2 playerPos = {player.x * CELL_SIZE, player.y * CELL_SIZE};
             Vector2 carPos = {c->x * CELL_SIZE, c->y * CELL_SIZE};
             float distance = CalculateDistance(playerPos, carPos);

             float volume = 1.0f - (distance / 500.0f);
             if (volume < 0.0f) volume = 0.0f;
             SetSoundVolume(carSound, volume);

             PlaySound(carSound); // Mainkan suara
              carSoundCooldown = CAR_SOUND_INTERVAL; // Reset timer setelah main suara
            }
            curr = curr->next;
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

    // **Reset kondisi permainan**
    kalah = false;
    PermainanBerakhir = false;
    player.score = 0;
    player.lives = MAX_LIVES;  
    numCars = NUM_CARS_START; 
    carSpeed = CAR_SPEED_START;  
    
    

    // **Reset posisi awal pemain**
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

    CreateEmpty(&carList); // Inisialisasi list mobil

    for (int i = 0; i < NUM_CARS_START; i++) {
        int col = rand() % (GRID_WIDTH - GRID_START);
        int row = array[i];
        int direction = directray[i];
        Car newCar = {col, row, carSpeed, direction};
        newCar.type = rand() % 4;

        InsertFirst(&carList, newCar);
    }

    // **Reset kamera ke posisi awal**
    camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
    camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.7f;

    printf("=== INITGAME SELESAI! Semua variabel kembali ke awal ===\n");
}

void ResetCombo()
{
    comboMultiplier = 1;
    comboStreak = 0;
}

void CheckCollision() {
    address curr = carList.First;
    while (curr != NULL) {
        Car *c = &curr->info;

        bool collision = false;
        if (c->direction == 1){
            collision = ((player.x <= c->x + 7) && (player.x >= c->x - 2.3)) &&
                        ((player.y <= c->y + 2.7) && (player.y >= c->y - 2));
        } else {
            collision = ((player.x <= c->x - 3) && (player.x >= c->x - 9.3)) &&
                        ((player.y <= c->y + 2.7) && (player.y >= c->y - 2));
        }

        if (collision) {
            player.x = checkpoint.x;
            player.y = checkpoint.y;
            player.lives--;
            ResetCombo();
            if (player.lives <= 0) kalah = true;
            break;
        }

        curr = curr->next;
    }
}

void UpdateGame(Camera2D *camera)
{
    if (!gameStarted) 
    {
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) 
        {
            gameStarted = true; // Mulai permainan saat tombol pertama ditekan
        }
        return; // Jangan update posisi player sebelum permainan dimulai
    }

    if (!PermainanBerakhir)
    {
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

        if (player.y>=GRID_HEIGHT)player.y = GRID_HEIGHT-1;

        checkposition(&player);
        CheckCollision();
    }

    if (player.y == 0)
    {
        NextLevel(camera, &player);
    }
}

float CalculateDistance(Vector2 pos1, Vector2 pos2) {
    return sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
} 