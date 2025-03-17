#ifndef HEADERANDREW_H
#define HEADERANDREW_H
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void RenderRoads();
void RenderCars(int *numCars, Car cars[]);
void RenderCharacter(Texture2D *PlayerSprite, Player player);
void LoadAllTextures();
void UnloadAllTextures();
void RenderInstructions(Player player, char *coordText, int level);                                        

#endif