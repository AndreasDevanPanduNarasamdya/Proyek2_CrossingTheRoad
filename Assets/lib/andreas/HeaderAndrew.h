#ifndef HEADERANDREW_H
#define HEADERANDREW_H

#include "../raylib.h"

Texture2D TaxiTexture, TruckTexture, VanTexture, PlayerSprite, background, logs, checkpointflag, checkpointtxt, Mustang, healthup, points;
bool showCheckpointText = false;
int checkpointTimer = 0;
int timer = 2000;
int lastscore;

void DefineArrayCord();
void RenderRoads();
void RenderCars(int *numCars, Car cars[]);
void RenderCharacter(Texture2D *PlayerSprite, Player player);
void LoadAllTextures();
void UnloadAllTextures();
void RenderInstructions(Player player, char *coordText, int level);                                        

#endif