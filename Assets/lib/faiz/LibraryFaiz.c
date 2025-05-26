#include "LibraryFaiz.h"
#include "../andreas/HeaderAndrew.h"
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
     // Posisi X agar teks di tengah    
    int y = SCREEN_HEIGHT / 2 - fontSize / 2;    // Posisi Y agar teks di tengah

    DrawText(text, x, y, fontSize, color);
}

void DrawGame(Camera2D camera, Checkpoint *Home, HealthHP *Health, PointsXP *Points)
{
    BeginDrawing();
    ClearBackground(WHITE);
    BeginMode2D(camera);

    sprintf(coordText, "Coordinate: %2d,%2d", player.x, player.y);
    RenderRoads(SCREEN_WIDTH, SCREEN_HEIGHT);

    RenderCars(&carList);

    RenderFlags(Home);

    RenderHealths(Health);

    RenderPoints(Points);

    RenderCharacter(&PlayerSprite, player);
    DrawParticles();
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

            c->x = newX;
           
            Vector2 playerPos = {player.x * CELL_SIZE, player.y * CELL_SIZE};
            Vector2 carPos = {c->x * CELL_SIZE, c->y * CELL_SIZE};
            float distance = CalculateDistance(playerPos, carPos);

            float maxDistance = 500.0f;
            float volume = 1.0f - (distance / maxDistance);
            if (volume < 0.0f)
                volume = 0.0f;
            SetSoundVolume(carSound, volume);

            if (!IsSoundPlaying(carSound)) {
                PlaySound(carSound);
            }

            curr = curr->next;
        }

        frameCounter = 0;
    }
}


void InitGrid(Checkpoint *Home, HealthHP *Health, PointsXP *Points)
{
    Checkpoint TempCheck = *Home;
    HealthHP TempHealth = *Health;
    PointsXP TempPoints = *Points;
    if (level == 1)
    {
        TempCheck->chckpointgrid[166][23] = CHECKPOINT_LINE;
        TempCheck->Next->chckpointgrid[39][53] = CHECKPOINT_LINE;

        TempHealth->healthgrid[131][51] = HEALTH_UP;
        TempHealth->Next->healthgrid[53][37] = HEALTH_UP;

        TempPoints->pointgrid[151][29] = POINTS;
        TempPoints->Next->pointgrid[21][76] = POINTS;
    }
    InitGrids(Home, Health, Points);
}

void ResetCameraCheckpoint(Player *player, Camera2D *camera){
    player->x = checkpoint.x;
    player->y = checkpoint.y;
    camera->target.y = player->y * CELL_SIZE;
}

void checkposition(Player *player, Checkpoint *Home, HealthHP *Health, PointsXP *Points)
{
    Checkpoint TempCheck = *Home;
    HealthHP current = *Health;
    PointsXP currents = *Points;
    Checkpoint prev = NULL;

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
        PlayCheckpointSound();
        checkpositions(player, Home, Health, Points);
        player->score += 100 * comboMultiplier;
        
    }

    else if (grid[player->y][player->x] == HEALTH_UP)
    {
        checkpositions(player,Home, Health, Points);
        // Clean up the player’s current grid tile
        grid[player->y][player->x] = ROAD;

    }


    else if (grid[player->y][player->x] == POINTS)
    {  
        checkpositions(player, Home, Health, Points);
        // Clean up the player’s current grid tile
        grid[player->y][player->x] = ROAD;
    }
}


void InitiateCheckpointlist(Checkpoint *First)
{
    *First = NULL;
    if (level == 1)
    {
        *First = (Checkpoint)malloc(sizeof(struct LinkedListCheckPoint));
        (*First)->enabled = true;
        (*First)->x = 500;
        (*First)->y = 375;
        (*First)->Before = NULL;

        (*First)->Next = (Checkpoint)malloc(sizeof(struct LinkedListCheckPoint));
        (*First)->Next->enabled = true;
        (*First)->Next->x = 200;
        (*First)->Next->y = 1650;
        (*First)->Next->Next = NULL;
        (*First)->Next->Before = (*First);
    }
}

void InitiateHealthList(HealthHP *Health)
{
    *Health = NULL;
    if (level == 1)
    {
        *Health = (HealthHP)malloc(sizeof(struct HealthyLife));
        (*Health)->enabled = true;
        (*Health)->x = 345;
        (*Health)->y = 548;
        (*Health)->Before = NULL;

        (*Health)->Next = (HealthHP)malloc(sizeof(struct HealthyLife));
        (*Health)->Next->enabled = true;
        (*Health)->Next->x = 478;
        (*Health)->Next->y = 1323;
        (*Health)->Next->Next = NULL;
        (*Health)->Next->Before = *Health;
    }
}

void InitiatePointsList(PointsXP *Points)
{
    *Points = NULL;

    if (level == 1)
    {
        *Points = (PointsXP)malloc(sizeof(struct CoinPoin));
        (*Points)->enabled = true;
        (*Points)->x = 178;
        (*Points)->y = 548;
        (*Points)->Before = NULL;

        (*Points)->Next = (PointsXP)malloc(sizeof(struct CoinPoin));
        (*Points)->Next->enabled = true;
        (*Points)->Next->x = 267;
        (*Points)->Next->y = 1523;
        (*Points)->Next->Next = NULL;
        (*Points)->Next->Before = *Points;
    }
}



void InitGame(Checkpoint *Home, HealthHP *Health, PointsXP *Points)
{
    srand(time(NULL));

    kalah = false;
    PermainanBerakhir = false;
    player.lives = MAX_LIVES;  
    numCars = NUM_CARS_START; 
    carSpeed = CAR_SPEED_START;          

    player.x = GRID_WIDTH / 2;
    player.y = GRID_HEIGHT - 2;
    checkpoint.x = player.x;
    checkpoint.y = player.y;



    InitiateCheckpointlist(Home);
    InitiateHealthList(Health);
    InitiatePointsList(Points);
    InitGrid(Home, Health, Points);

    
    int array[24] = {9, 14, 27, 32, 49, 55, 61, 67, 95, 101, 115, 121, 127, 133, 139, 145, 151, 157, 175, 181, 187, 193, 205, 211};
    int directray[24] = {-1, -1, 1, 1, -1, -1, 1, 1, /**/ 1, /**/ -1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, 1};

    InitGrid(Home, Health, Points); 

    CreateEmpty(&carList);

    for (int i = 0; i < NUM_CARS_START; i++) {
        int col = rand() % (GRID_WIDTH - GRID_START);
        int row = array[i];
        int direction = directray[i];
        Car newCar = {col, row, carSpeed, direction};
        newCar.type = rand() % 4;

        InsertFirst(&carList, newCar);
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

void CheckCollision(Camera2D *camera) {
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
            InitParticles((Vector2){player.x * CELL_SIZE, player.y *CELL_SIZE});
            player.x = checkpoint.x;
            player.y = checkpoint.y;
            player.lives--;
            ResetCameraCheckpoint(&player, camera);
            PlaySound(nabrak);
            ResetCombo();
            if (player.lives <= 0) {
                kalah = true;
                SoundGameover();
            }
            break;
        }

        curr = curr->next;
    }
}


void UpdateGame(Camera2D *camera, Checkpoint *Home, HealthHP *Health, PointsXP *Points) {

    if (!gameStarted) 
    {
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) 
        {
            gameStarted = true; // Mulai permainan saat tombol pertama ditekan
        }
        return; // Jangan update posisi player sebelum permainan dimulai
    }

    UpdateParticles();
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
            PlayPlayerMoveSound();           
            movement[0] = false;
        }
        if (movement[1])
        {
            player.y += PLAYER_SPEED + 1;
            PlayPlayerMoveSound();
            movement[1] = false;
        }
        if (movement[2])
        {
            player.x -= PLAYER_SPEED + 1;
            PlayPlayerMoveSound();
            movement[2] = false;
        }
        if (movement[3])
        {
            player.x += PLAYER_SPEED + 1;
            PlayPlayerMoveSound();
            movement[3] = false;
        }

        if (player.y>=GRID_HEIGHT)player.y = GRID_HEIGHT-1;

        checkposition(&player, Home, Health, Points);
        CheckCollision(camera);
    }

    if (player.y == 0)
    {
        NextLevel(camera, &player, Home, Health, Points);
    }
}

