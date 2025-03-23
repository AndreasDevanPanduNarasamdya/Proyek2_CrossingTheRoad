#ifndef LIBRARYAZZAM_H
#define LIBRARYAZZAM_H

#include "../GLOBALHEADER.h"
#include "../raylib.h"
#include "../faiz/LibraryFaiz.h"

#define MAX_PARTICLES 50  // Jumlah maksimal partikel efek

void NextLevel(); // Deklarasi fungsi NextLevel()

// Struct untuk partikel
typedef struct {
    Vector2 pos;
    Vector2 speed;
    int life;
} Particle;

// Deklarasi array partikel dan variabel status collision
extern Particle particles[MAX_PARTICLES];
extern bool playerHit;

// Deklarasi fungsi modul partikel
void InitParticles(Vector2 playerPos);
void UpdateParticles();
void DrawParticles();

#endif
