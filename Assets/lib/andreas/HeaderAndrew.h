#ifndef HEADERANDREW_H
#define HEADERANDREW_H

#include "../raylib.h"

Texture2D TaxiTexture, TruckTexture, VanTexture, background, logs, checkpointflag, checkpointtxt, Mustang, healthup, points, Train, lvl1background, lvl2background, lvl3background, PlayerSprite;
bool showCheckpointText = false;
int checkpointTimer = 0;
int timer = 2000;
int lastscore;

Vector2 *ItemCoords;

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
void RenderCharacter(Texture2D *PlayerSprite, Player player);
void LoadAllTextures();
void UnloadAllTextures();
void RenderInstructions(Player player, char *coordText, int level);                                        

#endif