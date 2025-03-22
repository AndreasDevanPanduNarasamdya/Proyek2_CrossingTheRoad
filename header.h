#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include "GLOBALHEADER.h"
#include <math.h>

bool isInMainMenu = true;
void start();
void NextLevel(Camera2D *camera, Player *player);

typedef enum {
    MENU_START,
    MENU_OPTIONS,
    MENU_EXIT
} MenuOption;


float CalculateDistance(Vector2 pos1, Vector2 pos2);
void StopCarSound();

MenuOption ShowMenu();
void ShowOptions(float *volume, bool *isFullscreen);
void ShowTryAgain(bool *restartGame);
void HandleGameOver(bool *kalah, bool *PermainanBerakhir); 

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
int comboMultiplier = 1;
int comboStreak = 0;
int comboThreshold = 3;

int grid[GRID_HEIGHT][GRID_WIDTH];

void DrawGame(Camera2D camera);
void InitGame();
void UpdateGame(Camera2D *camera);
void checkposition(Player *player);
void InitGrid();
void UpdateCarMovement();
void CheckCollision();
void ResetCombo();

void InitSounds();
void PlayMoveChar();
void PlayGetHealth();
void PlayGetCheckpoint();
void PlayPausedSound();
void PlayCarSound();
void UpdateSoundVolume(float volume); // Updated name for clarity
void UnloadSounds();

// Function prototypes for music
void InitMusic(); // Updated name
void PlayMenuBacksound();
void PlayBackgroundMusic1();
void UpdateMusicVolume(float volume); // Updated name
void UnloadMusic(); // Updated name

// Declare static variables for music and sound effects
extern Music backgroundMusic1, menuSound;

extern Sound moveChar, getHealth, getCheckpoint, pausedSound, carSound;

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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

void start();

#endif
