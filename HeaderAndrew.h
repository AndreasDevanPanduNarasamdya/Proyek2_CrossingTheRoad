#ifndef HEADERANDREW_H
#define HEADERANDREW_H
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Texture2D TaxiTexture, TruckTexture, VanTexture, background, logs, checkpointflag, checkpointtxt, Mustang, healthup, points, Train, lvl2background, lvl3background;
bool showCheckpointText = false;
int checkpointTimer = 0;
int timer = 2000;
int lastscore;

Vector2 *ItemCoords;

Texture2D PlayerSprite;

Texture2D FlagAsset[4], PointAsset[6], HealthAsset[6];

bool point1 = false, point2 = false, point3 = false, point4 = false;

typedef struct
{
    Texture2D PlayerFrontSprite;
    Texture2D PlayerBackSprite;
    Texture2D PlayerSideLeftSprite;
    Texture2D PlayerSideRightSprite;
    int countdown;
}CharaAnim;

CharaAnim Character;


void DefineArrayCord();
void RenderRoads();
void RenderCars(int *numCars, Car cars[]);
void LoadAllTextures();
void UnloadAllTextures();
void RenderInstructions(Player player, char *coordText, int level);                                        

#endif