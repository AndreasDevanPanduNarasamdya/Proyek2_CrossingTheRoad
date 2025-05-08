#ifndef HEADERANDREW_H
#define HEADERANDREW_H

#include "../raylib.h"

Texture2D TaxiTexture, TruckTexture, VanTexture, PlayerSprite, background, logs, checkpointflag, checkpointtxt, Mustang, healthup, points;
bool showCheckpointText = false;
int checkpointTimer = 0;
int timer = 2000;
int lastscore;

Texture2D FlagAsset[4], HealthAsset[6], PointAsset[6];

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
void RenderCharacter(Texture2D *PlayerSprite, Player player);
void Renderchkpointtxt();
void CheckpointLogic();
void RenderFlags(Checkpoint *First);
void ResetTimer();
void RenderHealths(HealthHP *Health);
void RenderPoints(PointsXP *Points);
void RenderCars(int *numCars, Car cars[]);
void UnloadAllTextures();
void LoadAllTextures();
void RenderInstructions(Player player, char *coordText, int level);

#endif