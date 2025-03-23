#ifndef GLOBALHEADER_H
#define GLOBALHEADER_H

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define CELL_SIZE 10
#define GRID_WIDTH 78
#define GRID_START 22
#define GRID_HEIGHT 220
#define PLAYER_SIZE 10
#define CAR_WIDTH 20
#define CAR_HEIGHT 10
#define NUM_CARS_START 24
#define PLAYER_SPEED 1
#define CAR_SPEED_START 1
#define CAR_MOVE_DELAY 6
#define LANE_COLOR DARKGRAY
#define MAX_LIVES 3
#define CAMERA_SPEED 1
#define CAMERA_DISTANCE 50
#define CAMERA_DEATH_DISTANCE 500
#define putihs 4
#define check 4
#define POINTS 5

#define ROAD 0
#define LANE_MARK 1
#define CHECKPOINT_LINE 2
#define HEALTH_UP 4
#define PLAYER 2
#define CAR 3

bool isPaused = false; // Apakah game sedang pause
float volume = 1.0f;   // Volume awal
bool isFullscreen = false; // Fullscreen mode awal


Vector2 CoordArr[SCREEN_WIDTH][SCREEN_HEIGHT];

bool passed;
int health_upgrade = 0;

typedef struct
{
    int x, y;
    bool enabled;

}HealthProp;


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