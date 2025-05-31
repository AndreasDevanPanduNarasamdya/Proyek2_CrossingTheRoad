#ifndef HEADERANDREW_H
#define HEADERANDREW_H

#include "../raylib.h"

Texture2D TaxiTexture, TruckTexture, VanTexture, PlayerSprite, background, newmap2,  logs, checkpointflag, checkpointtxt, lvl3, Mustang, healthup, points, newmap, train;
bool showCheckpointText = false;
int checkpointTimer = 0;
int timer = 2000;
int lastscore;
int lastlives;

Texture2D FlagAsset[4], HealthAsset[6], PointAsset[6], EggyAsset[6];

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
void RenderEggs(EggyPoints *Egg);
void RenderCars(Carlist *carList);
void UnloadAllTextures();
void LoadAllTextures();
void RenderInstructions(Player player, char *coordText, int level);
void InitiateCheckpointlist(Checkpoint *First);
void InitiateHealthList(HealthHP *Health);
void InitiatePointsList(PointsXP *Points);
void InitiateEggsList(EggyPoints *Egg);
void InitGrids(Checkpoint *Home, HealthHP *Health, PointsXP *Points, EggyPoints *Egg);
void checkposition(Player *player, Checkpoint *Home, HealthHP *Health, PointsXP *Points, EggyPoints *Egg);
// void InitGrids(Checkpoint *Home, HealthHP *Health, PointsXP *Points);
// void checkpositions(Player *player, Checkpoint *Home, HealthHP *Health, PointsXP *Points);

#endif