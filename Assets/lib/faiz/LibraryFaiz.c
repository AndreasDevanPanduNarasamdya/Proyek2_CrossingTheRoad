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

void DrawGame(Camera2D camera, Checkpoint *Home, HealthHP *Health, PointsXP *Points, EggyPoints *Egg)
{
    BeginDrawing();
    ClearBackground(WHITE);
    BeginMode2D(camera);

    sprintf(coordText, "Coordinate: %2d,%2d", player.x, player.y);
    RenderRoads();

    RenderCars(&carList);

    RenderFlags(Home);

    RenderHealths(Health);

    RenderPoints(Points);

    RenderEggs(Egg);

    RenderCharacter(&PlayerSprite, player);

    // Hitung progress bar
    float progress = CalculateProgress(&player, FINISH_Y);  // Hitung progress
    
    // Gambar partikel darah
    DrawParticles();
    DrawCheckpointParticles();


    // Selesai menggambar elemen dalam dunia
    EndMode2D();

    // Gambar progress bar
    DrawProgressBar(progress);

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
}

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


void InitGrid(Checkpoint *Home, HealthHP *Health, PointsXP *Points, EggyPoints *Egg)
{
    Checkpoint TempCheck = *Home;
    HealthHP TempHealth = *Health;
    PointsXP TempPoints = *Points;
    EggyPoints EggTemp = *Egg;

    InitGrids(&TempCheck, &TempHealth, &TempPoints, &EggTemp);    //InitGrids(Home, Health, Points);
    while (TempCheck != NULL)
    {
        for (int i = 0; i < GRID_WIDTH; i++)
        {
            for (int j = 0; j < GRID_HEIGHT; j++)
            {
                if (TempCheck->chckpointgrid[j][i] == CHECKPOINT_LINE)
                {
                    for (int p = i - 5; p < i + 5; p++) 
                    {
                        for (int o = j - 5; o < j + 5; o++) 
                        {
                            if (p >= 0 && p < GRID_WIDTH && o >= 0 && o < GRID_HEIGHT) 
                            {
                                grid[o][p] = CHECKPOINT_LINE;
                            }
                        }
                    }
                }
            }
        }
        TempCheck = TempCheck->Next;
    }
    while (TempHealth != NULL)
    {
        PlayCheckpointSound();
        //checkposition(player, Home, Health, Points);
        player.score += 100 * comboMultiplier;
        for (int i = 0; i < GRID_WIDTH; i++)
        {
            for (int j = 0; j < GRID_HEIGHT; j++)
            {
                if (TempHealth->healthgrid[j][i] == HEALTH_UP)
                {
                    for (int p = i - 5; p < i + 5; p++) 
                    {
                        for (int o = j - 5; o < j + 5; o++) 
                        {
                            if (p >= 0 && p < GRID_WIDTH && o >= 0 && o < GRID_HEIGHT) 
                            {
                                grid[o][p] = HEALTH_UP;
                            }
                        }
                    }
                }
            }
        }
        TempHealth->enabled = true;
        TempHealth = TempHealth->Next;
    }
    while (TempPoints != NULL)
    {
        //checkposition(*player,Home, Health, Points);
        for (int i = 0; i < GRID_WIDTH; i++)
        {
            for (int j = 0; j < GRID_HEIGHT; j++)
            {
                if (TempPoints->pointgrid[j][i] == POINTS)
                {
                    for (int p = i - 5; p < i + 5; p++) 
                    {
                        for (int o = j - 5; o < j + 5; o++) 
                        {
                            if (p >= 0 && p < GRID_WIDTH && o >= 0 && o < GRID_HEIGHT) 
                            {
                                grid[o][p] = POINTS;
                            }
                        }
                    }
                }
            }
        }
        TempPoints = TempPoints->Next;
    }
    while (EggTemp != NULL)
    {
        for (int i = 0; i < GRID_WIDTH; i++)
        {
            for (int j = 0; j < GRID_HEIGHT; j++)
            {
                if (EggTemp->Eggygrid[j][i] == EGG)
                {
                    for (int p = i - 5; p < i + 5; p++) 
                    {
                        for (int o = j - 5; o < j + 5; o++) 
                        {
                            if (p >= 0 && p < GRID_WIDTH && o >= 0 && o < GRID_HEIGHT) 
                            {
                                grid[o][p] = EGG;
                            }
                        }
                    }
                }
            }
        }
        EggTemp = EggTemp->Next;
    }
}

void ResetCameraCheckpoint(Player *player, Camera2D *camera){
    player->x = checkpoint.x;
    player->y = checkpoint.y;
    camera->target.y = player->y * CELL_SIZE;
}

void InitGame(Checkpoint *Home, HealthHP *Health, PointsXP *Points, EggyPoints *Egg)
{
    srand(time(NULL));

    kalah = false;
    PermainanBerakhir = false;
    player.score = 0;
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
    InitiateEggsList(Egg);
    InitGrid(Home, Health, Points, Egg);

    
    int array[25] = {9, 14, 27, 32, 49, 55, 61, 67, 77, 95, 101, 115, 121, 127, 133, 141, 145, 151, 157, 175, 181, 187, 193, 208, 212};
    int directray[25] = {-1, -1, 1, 1, -1, -1, 1, 1, -1,/**/ 1, /**/ -1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, 1};

    InitGrid(Home, Health, Points, Egg); 

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
                        ((player.y <= c->y + 2.3) && (player.y >= c->y - 5));
        } else {
            collision = ((player.x <= c->x - 3) && (player.x >= c->x - 9.3)) &&
                        ((player.y <= c->y + 2.5) && (player.y >= c->y - 5));
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


void UpdateGame(Camera2D *camera, Checkpoint *Home, HealthHP *Health, PointsXP *Points, EggyPoints *Egg) {
    

    if (!gameStarted) 
    {
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) 
        {
            gameStarted = true; // Mulai permainan saat tombol pertama ditekan
        }
        return; // Jangan update posisi player sebelum permainan dimulai
    }

    UpdateParticles();
    UpdateCheckpointParticles();
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

        checkposition(&player, Home, Health, Points, Egg);
        CheckCollision(camera);
    }

    if (player.y == 0)
    {
        NextLevel(camera, &player, Home, Health, Points, Egg);
    }
}

