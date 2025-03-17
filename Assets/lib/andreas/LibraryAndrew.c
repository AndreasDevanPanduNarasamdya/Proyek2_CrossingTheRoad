#include "../raylib.h"
#include "HeaderAndrew.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../GLOBALHEADER.h"
#include "../azzam/LibraryAzzam.h"
#include "../faiz/LibraryFaiz.h"



void RenderRoads() {
    for (int y = 0; y < GRID_HEIGHT; y++) {
        for (int x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x] == LANE_MARK) {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
            } else if (grid[y][x] == putihs) {
                DrawRectangle(x * CELL_SIZE + CELL_SIZE / 4, y * CELL_SIZE + CELL_SIZE / 4, CELL_SIZE / 2, CELL_SIZE / 8, YELLOW);
            } else if (grid[y][x]== ROAD) {
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, GRAY);
            } else if (grid[y][x]== CHECKPOINT_LINE){
                DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLUE);
            }
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
    TaxiTexture = LoadTexture("Assets/sprite/taxi.png");
    TruckTexture = LoadTexture("Assets/sprite/gruppesechs_van.png");
    VanTexture = LoadTexture("Assets/sprite/vanbankk.png");
    PlayerSprite = LoadTexture("Assets/sprite/npcmoment.png");
    background = LoadTexture("Assets/sprite/longroad2lanes.png");
}

void RenderInstructions(Player player, char *coordText, int level)
{
    int margin = 20; // Margin dari tepi layar

    // Menampilkan teks di sudut kiri atas layar
    DrawText(TextFormat("Score: %d", player.score), margin, margin, 20, BLACK);
    DrawText(TextFormat("Lives: %d", player.lives), margin, margin + 30, 20, BLACK);
    DrawText(TextFormat("Level: %d", level), margin, margin + 60, 20, BLACK);
    DrawText(coordText, margin, margin + 90, 20, BLACK);
    DrawText("Use Arrow Keys to Move", margin, margin + 120, 20, BLACK);

}