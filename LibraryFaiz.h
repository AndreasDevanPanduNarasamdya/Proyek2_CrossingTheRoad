#ifndef LIBRARYFAIZ_H
#define LIBRARYFAIZ_H
#include "GLOBALHEADER.h"
#include "raylib.h"

Player player;
vector checkpoint;
Car cars[NUM_CARS_START * 2];
Camera2D camera = {0};
int frameCounter = 0;
int ScorTerakhir = -1;
bool PermainanBerakhir = false;
bool kalah = false;
int level = 1;
int numCars = NUM_CARS_START;
int carSpeed = CAR_SPEED_START;
bool movement[4] = {false,false,false,false};
char coordText[50];

void InitGame();
void UpdateGame();
void NextLevel();
void checkposition(Player *player, vector *check);


#endif
