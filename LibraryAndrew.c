#include "raylib.h"
#include "GLOBALHEADER.h"
#include "HeaderAndrew.h"
#include "LibraryFaiz.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int margin = 20;

void DefineArrayCord()
{
    //int x;
    //int y;
    Vector2 ScreenVector;
    for (ScreenVector.x = 0; ScreenVector.x <= SCREEN_WIDTH; ++ScreenVector.x )
    {
        for (ScreenVector.y = 0; ScreenVector.y <= SCREEN_HEIGHT; ++ScreenVector.y)
        {
            CoordArr[(int)ScreenVector.x][(int)ScreenVector.y] = ScreenVector;
        }
    }
}
void RenderRoads()
{
            DrawTextureEx(background, (Vector2){150,0}, 0.0f, 0.25, WHITE);
}

void RenderCharacter(Texture2D *PlayerSprite, Player player)
{
    DrawTextureEx(*PlayerSprite, (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE}, 0.0f, 0.1f, WHITE);
}


void Renderchkpointtxt() 
{
        DrawTextureEx(checkpointtxt, (Vector2){margin + 240, margin}, 0, 0.2, WHITE);
}

// Call this function **every frame** in the game loop
void CheckpointLogic() {
    if (player.score > lastscore) {
        lastscore = player.score;  // Update last score
        showCheckpointText = true;
        checkpointTimer = 300;  // Show for 300 frames (~5 seconds at 60 FPS)
    }
}

void RenderFlags()
{
    DrawTextureEx(checkpointflag, (Vector2){500, 375}, 0.0f, 0.1, WHITE);
    DrawTextureEx(checkpointflag, (Vector2){200, 1650}, 0.0f, 0.1, WHITE);
}

void ResetTimer()
{
    if (passed == true)
    {
        Renderchkpointtxt();
        timer -= GetFrameTime() * 1000;
        if (timer <= 0)
        {
            passed = false;
            timer = 2000;
        }
    }
}

void RenderHealths()
{
    DrawTextureEx(healthup, (Vector2){345, 548}, 0.0f, 0.07, WHITE);
    DrawTextureEx(healthup, (Vector2){478, 1323}, 0.0f, 0.07, WHITE);
}

void RenderPoints()
{
    DrawTextureEx(points, (Vector2){178, 548}, 0.0f, 0.07, WHITE);
    DrawTextureEx(points, (Vector2){267, 1523}, 0.0f, 0.07, WHITE);
}

 void RenderCars(int *numCars, Car cars[])
{
    for (int i = 0; i < *numCars; i++)  // Use *numCars instead of numCars
    {
        int x = cars[i].x * CELL_SIZE;
        int y = cars[i].y * CELL_SIZE;
        Texture2D carTexture;

        if (y != 95 * CELL_SIZE && y != 101 * CELL_SIZE) 
        {
            if (cars[i].type == 0) 
            {
                carTexture = TaxiTexture;
            }
            else if (cars[i].type == 1) 
            {
                carTexture = TruckTexture;
            }  
            else if (cars[i].type == 2)
            {
                carTexture = VanTexture;
            }
            else if (cars[i].type == 3)
            {
                carTexture = Mustang;
            }
        }
        else
        {
            carTexture = logs;
        }
        if (cars[i].direction == 1)
        {
            if (y != 95 * CELL_SIZE && y != 101 * CELL_SIZE)
            {
                DrawTextureEx(carTexture, (Vector2){x,y}, 0.0f, 0.03f, WHITE);
            }
            else
            {
                DrawTextureEx(carTexture, (Vector2){x,y}, 0.0f, 0.1f, WHITE);
            }
        }
        else 
        {
            if (y != 95 * CELL_SIZE && y != 101 * CELL_SIZE)
            {
                DrawTextureEx(carTexture, (Vector2){x,y+40}, 180.0f, 0.03f, WHITE);
            }
            else
            {
                DrawTextureEx(carTexture, (Vector2){x,y+40}, 180.0f, 0.1f, WHITE);
            }
        }
        
    }
}

void UnloadAllTextures()
{
    UnloadTexture(TaxiTexture);
    UnloadTexture(TruckTexture);
    UnloadTexture(VanTexture);
    UnloadTexture(Mustang);
    UnloadTexture(background);
    UnloadTexture(PlayerSprite);
    UnloadTexture(checkpointtxt);
    UnloadTexture(healthup);
}

void LoadAllTextures()
{
    TaxiTexture = LoadTexture("Assets/taxi.png");
    TruckTexture = LoadTexture("Assets/gruppesechs_van.png");
    VanTexture = LoadTexture("Assets/vanbankk.png");
    Mustang = LoadTexture("Assets/mustang.png");
    PlayerSprite = LoadTexture("Assets/npcmoment.png");
    background = LoadTexture("Assets/mapproyek2.png");
    logs = LoadTexture("Assets/logbridge.png");
    checkpointflag = LoadTexture("Assets/checkpointflag.png");
    checkpointtxt = LoadTexture("Assets/checkpointtxt.png");
    healthup = LoadTexture("Assets/healthpowerup.png");
    points = LoadTexture("Assets/pointsup.png");
}

void RenderInstructions(Player player, char *coordText, int level)
{

    // Menampilkan teks di sudut kiri atas layar
    DrawText(TextFormat("Score: %d", player.score), margin, margin, 20, WHITE);
    DrawText(TextFormat("Lives: %d", player.lives), margin, margin + 30, 20, WHITE);
    DrawText(TextFormat("Level: %d", level), margin, margin + 60, 20, WHITE);
    DrawText(coordText, margin, margin + 90, 20, WHITE);
    DrawText("Use Arrow Keys to Move", margin, margin + 120, 20, WHITE);
    DrawText(TextFormat("health: %d", health_upgrade), margin, margin + 150, 20, WHITE);
}

