#ifndef LIBRARYFAIZ_H
#define LIBRARYFAIZ_H

Player player;
vector checkpoint;
Car cars[NUM_CARS_START * 2];
Camera2D camera = {0};
int frameCounter = 0;
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
int lastScorePosition = 0;
bool gameStarted = false;

int grid[GRID_HEIGHT][GRID_WIDTH];
address Alokasi(Car carData);
void CreateEmpty(Carlist *L);
void InsertFirst(Carlist *L, Car carData);
void DrawGame(Camera2D camera);
void InitGame();
void UpdateGame(Camera2D *camera);
void checkposition(Player *player);
void InitGrid();
void UpdateCarMovement();
void CheckCollision();
void ResetCombo();
void DrawCenteredText(const char *text, int fontSize, Color color);
float CalculateDistance(Vector2 pos1, Vector2 pos2);

#endif
