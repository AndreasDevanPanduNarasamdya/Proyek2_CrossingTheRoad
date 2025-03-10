#include "raylib.h"
#include "GLOBALHEADER.h"
#include "HeaderAndrew.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void RenderRoads()
{
    for (int x = 0; x < SCREEN_WIDTH; x += background.width) 
    {
        for (int y = 0; y < SCREEN_HEIGHT*2.5; y += 300) 
        {
            DrawTextureEx(background, (Vector2){x, y}, 0.0f, 0.25, WHITE);
        }
    }
}

void RenderCharacter(Texture2D *PlayerSprite, Player player)
{
    DrawTextureEx(*PlayerSprite, (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE}, 0.0f, 0.1f, WHITE);
}

 void RenderCars(int *numCars, Car cars[])
{
    for (int i = 0; i < *numCars; i++)  // Use *numCars instead of numCars
    {
        int x = cars[i].x * CELL_SIZE;
        int y = cars[i].y * CELL_SIZE;
        Texture2D carTexture;

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
        
        DrawTextureEx(carTexture, (Vector2){x, y}, 0.0f, 0.03f, WHITE);
    }
}

void UnloadAllTextures()
{
    UnloadTexture(TaxiTexture);
    UnloadTexture(TruckTexture);
    UnloadTexture(VanTexture);
    UnloadTexture(background);
    UnloadTexture(PlayerSprite);
}

void LoadAllTextures()
{
    TaxiTexture = LoadTexture("Assets/taxi.png");
    TruckTexture = LoadTexture("Assets/gruppesechs_van.png");
    VanTexture = LoadTexture("Assets/vanbankk.png");
    PlayerSprite = LoadTexture("Assets/npcmoment.png");
    background = LoadTexture("Assets/longroad2lanes.png");
}

void RenderInstructions(Player player, char *coordText, int level)
{
    DrawText(TextFormat("Score: %d", player.score), player.x *CELL_SIZE - 400, player.y * CELL_SIZE - 400, 20, WHITE);
    DrawText(TextFormat("Lives: %d", player.lives),  player.x *CELL_SIZE - 400, player.y * CELL_SIZE - 350, 20, WHITE);
    DrawText(TextFormat("Level: %d", level), player.x * CELL_SIZE - 400, player.y * CELL_SIZE - 300, 20, WHITE);
    DrawText(coordText, player.x * CELL_SIZE - 400, player.y * CELL_SIZE - 200, 20, WHITE);
    DrawText("Use Arrow Keys to Move", player.x * CELL_SIZE - 400, player.y * CELL_SIZE - 250, 20, WHITE);
}
