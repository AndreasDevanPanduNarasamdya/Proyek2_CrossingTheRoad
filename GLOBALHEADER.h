#ifndef GLOBALHEADER_H
#define GLOBALHEADER_H
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define CELL_SIZE 10
#define GRID_WIDTH 100
#define GRID_HEIGHT 200
#define PLAYER_SIZE 10
#define CAR_WIDTH 20
#define CAR_HEIGHT 10
#define NUM_CARS_START 20
#define PLAYER_SPEED 1
#define CAR_SPEED_START 1
#define CAR_MOVE_DELAY 6
#define LANE_COLOR DARKGRAY
#define MAX_LIVES 3
#define CAMERA_SPEED 1
#define CAMERA_DISTANCE 50
#define CAMERA_DEATH_DISTANCE 500

#define ROAD 0
#define LANE_MARK 1
#define CHECKPOINT_LINE 2
#define PLAYER 2
#define CAR 3

Texture2D TaxiTexture, TruckTexture, VanTexture, PlayerSprite, background;

typedef struct {
    int x, y;
    int speed;
    int direction;
    int type;
} Car;

typedef struct {
    int x, y, score, lives;
} Player;

typedef struct vector {
    int x, y;
} vector;

#endif