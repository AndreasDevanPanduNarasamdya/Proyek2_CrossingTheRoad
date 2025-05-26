#ifndef LIBRARYAZZAM_H
#define LIBRARYAZZAM_H


void NextLevel(Camera2D *camera, Player *player, Checkpoint *Home, HealthHP *Health, PointsXP *Points); // Deklarasi fungsi NextLevel()

#define MAX_PARTICLES 50  // Jumlah maksimal partikel efek

#define START_Y (GRID_HEIGHT - 2)
#define FINISH_Y 0 // Atau y berapa pun garis finish kamu berada

//void NextLevel(); // Deklarasi fungsi NextLevel()

#define MAX_CHECKPOINT_PARTICLES 50

typedef struct {
    Vector2 pos;
    Vector2 speed;
    int life;
    float size;
    Color color;
} Particle;


Particle checkpointParticles[MAX_CHECKPOINT_PARTICLES];


// Deklarasi array partikel dan variabel status collision
Particle particles[MAX_PARTICLES];
bool playerHit;

// Deklarasi fungsi modul partikel
void InitParticles(Vector2 playerPos);
void UpdateParticles();
void DrawParticles();

// Deklarasi Partikel Checkpoint
void InitCheckpointParticles(Vector2 checkpointPos);
void UpdateCheckpointParticles();
void DrawCheckpointParticles();

// Modul Progress Bar
void DrawProgressBar(float currentProgress); // Deklarasi fungsi gambar progress bar
float CalculateProgress(Player *player, int finishY); // Deklarasi fungsi hitung progress


#endif
