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
#define CAR_SPEED_START 2
#define CAR_MOVE_DELAY 6
#define LANE_COLOR DARKGRAY
#define MAX_LIVES 3
#define CAMERA_SPEED 1
#define CAMERA_DISTANCE 50
#define CAMERA_DEATH_DISTANCE 500
#define putihs 4
#define check 4

#define POINTS 6
#define EGG 7
#define ROAD 0
#define LANE_MARK 1
#define CHECKPOINT_LINE 5
#define HEALTH_UP 4
#define PLAYER 2
#define CAR 3

bool isPaused = false; // Apakah game sedang pause
float volume = 1.0f;   // Volume awal
bool isFullscreen = false; // Fullscreen mode awal

bool passed;
int health_upgrade = 0;

typedef struct LinkedListCheckPoint
{
    int chckpointgrid[GRID_HEIGHT][GRID_WIDTH];
    int x, y;
    bool enabled;
    struct LinkedListCheckPoint *Next;
    struct LinkedListCheckPoint *Before;
}*Checkpoint;

typedef struct HealthyLife
{
    int healthgrid[GRID_HEIGHT][GRID_WIDTH];
    int x, y;
    bool enabled;
    struct HealthyLife *Next;
    struct HealthyLife *Before;
}*HealthHP;

typedef struct CoinPoin
{
    int pointgrid[GRID_HEIGHT][GRID_WIDTH];
    int x, y;
    bool enabled;
    struct CoinPoin *Next;
    struct CoinPoin *Before;
}*PointsXP;

typedef struct Eggy
{
    int Eggygrid[GRID_HEIGHT][GRID_WIDTH];
    int x, y;
    bool enabled;
    struct Eggy *Next;
    struct Eggy *Before;
}*EggyPoints;



typedef struct {
    int x, y, score, lives;
} Player;

typedef struct vector {
    int x, y;
} vector;

typedef struct {
    int x, y;
    int speed;
    int direction;
    int type;
} Car;

typedef Car infotype; 
typedef struct tElmtList *address;
typedef struct tElmtList {
    infotype info;     
    address next;
} ElmtList;

typedef struct {
    address First;
} List;

typedef List Carlist;

Carlist carList;

#endif