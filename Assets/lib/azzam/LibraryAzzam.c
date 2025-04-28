#include "../header.h"

// Variabel global untuk modul partikel (tidak didefinisikan di LibraryFaiz.h)
Particle particles[MAX_PARTICLES];  // Array partikel
bool playerHit = false;             // Status collision


void NextLevel(Camera2D *camera, Player *player) {
    // Tingkatkan level
    ++level;
    
    // Reset posisi pemain ke tengah bawah grid
    player->x = GRID_WIDTH / 2;
    player->y = GRID_HEIGHT - 2;  // Kurangi 2 agar tidak keluar batas
    
    checkpoint.x = player->x;
    checkpoint.y = player->y;

    // Reset posisi kamera ke awal
    camera->target.y = player->y * CELL_SIZE;
    // Inisialisasi ulang game untuk level baru
    InitGame();
}

// --- Modul Efek Partikel ---
// Inisialisasi partikel saat terjadi collision
void InitParticles(Vector2 playerPos) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].pos = playerPos;
        particles[i].speed = (Vector2){ GetRandomValue(-3, 3), GetRandomValue(-5, -1) };
        particles[i].life = GetRandomValue(20, 40);  // Lama hidup acak
    }
}

// Update pergerakan partikel setiap frame
void UpdateParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].life > 0) {
            particles[i].pos.x += particles[i].speed.x;
            particles[i].pos.y += particles[i].speed.y;
            particles[i].speed.y += 0.2;  // Efek gravitasi
            particles[i].life--;
        }
    }
}

// Render partikel di layar
void DrawParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].life > 0) {
            // Warna partikel dengan efek fade-out: opacity tergantung pada life
            Color particleColor = (Color){255, 50, 50, particles[i].life * 8};
            DrawCircle((int)particles[i].pos.x, (int)particles[i].pos.y, 3, particleColor);
        }
    }
}