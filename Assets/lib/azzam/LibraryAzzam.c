#include "../header.h"

// Variabel global untuk modul partikel (tidak didefinisikan di LibraryFaiz.h)
Particle particles[MAX_PARTICLES];  // Array partikel
bool playerHit = false;             // Status collision


void NextLevel(Camera2D *camera, Player *player, Checkpoint *Home, HealthHP *Health, PointsXP *Points) {
    // Tingkatkan level
    level++;
    
    // Reset posisi pemain ke tengah bawah grid
    player->x = GRID_WIDTH / 2;
    player->y = GRID_HEIGHT - 2;  // Kurangi 2 agar tidak keluar batas
    
    checkpoint.x = player->x;
    checkpoint.y = player->y;

    // Reset posisi kamera ke awal
    camera->target.y = player->y * CELL_SIZE;
    // Inisialisasi ulang game untuk level baru
    InitGame(Home, Health, Points);
}

// --- Modul Efek Partikel ---
// Inisialisasi partikel saat terjadi collision
// Struktur partikel yang diperbaiki

// Inisialisasi partikel dengan variasi yang lebih menarik
void InitParticles(Vector2 playerPos) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        // Offset posisi sedikit untuk efek ledakan yang lebih natural
        particles[i].pos.x = playerPos.x + GetRandomValue(-10, 10);
        particles[i].pos.y = playerPos.y + GetRandomValue(-10, 10);
        
        // Kecepatan dengan pola melingkar untuk efek ledakan
        float angle = GetRandomValue(0, 360) * DEG2RAD;
        float velocity = GetRandomValue(2, 6);
        particles[i].speed.x = cosf(angle) * velocity;
        particles[i].speed.y = sinf(angle) * velocity - GetRandomValue(1, 3); // Bias ke atas
        
        // Hidup partikel dengan variasi
        particles[i].maxLife = GetRandomValue(30, 60);
        particles[i].life = particles[i].maxLife;
        
        // Ukuran partikel bervariasi
        particles[i].size = GetRandomValue(2, 5);
        
        // Variasi warna partikel (merah, oranye, kuning)
        int colorType = GetRandomValue(0, 2);
        switch(colorType) {
            case 0: particles[i].color = (Color){255, 50, 50, 255}; break;   // Merah
            case 1: particles[i].color = (Color){255, 150, 50, 255}; break;  // Oranye
            case 2: particles[i].color = (Color){255, 255, 100, 255}; break; // Kuning
        }
    }
}

// Update partikel dengan physics yang lebih realistis
void UpdateParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].life > 0) {
            // Update posisi
            particles[i].pos.x += particles[i].speed.x;
            particles[i].pos.y += particles[i].speed.y;
            
            // Gravitasi bertahap
            particles[i].speed.y += 0.15;
            
            // Resistansi udara (drag)
            particles[i].speed.x *= 0.98;
            particles[i].speed.y *= 0.99;
            
            // Kurangi ukuran partikel seiring waktu
            particles[i].size *= 0.98;
            
            // Kurangi hidup partikel
            particles[i].life--;
        }
    }
}

// Render partikel dengan efek visual yang lebih menarik
void DrawParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].life > 0) {
            // Hitung alpha berdasarkan sisa hidup
            float lifeRatio = (float)particles[i].life / particles[i].maxLife;
            int alpha = (int)(255 * lifeRatio);
            
            // Terapkan alpha ke warna partikel
            Color particleColor = particles[i].color;
            particleColor.a = alpha;
            
            // Gambar partikel dengan ukuran yang berubah
            DrawCircleV(particles[i].pos, particles[i].size, particleColor);
            
            // Efek tambahan: lingkaran luar untuk glow effect
            if (lifeRatio > 0.7) {
                Color glowColor = particleColor;
                glowColor.a = alpha / 4;
                DrawCircleV(particles[i].pos, particles[i].size + 2, glowColor);
            }
        }
    }
}

// Fungsi untuk partikel spark kecil (opsional - efek tambahan)
void InitSparkParticles(Vector2 playerPos) {
    // Tambahan: partikel spark kecil untuk efek lebih dramatis
    for (int i = 0; i < 15; i++) {
        particles[MAX_PARTICLES - 15 + i].pos = playerPos;
        
        // Kecepatan random untuk spark
        particles[MAX_PARTICLES - 15 + i].speed.x = GetRandomValue(-8, 8);
        particles[MAX_PARTICLES - 15 + i].speed.y = GetRandomValue(-8, -2);
        
        // Hidup pendek untuk spark
        particles[MAX_PARTICLES - 15 + i].maxLife = GetRandomValue(10, 20);
        particles[MAX_PARTICLES - 15 + i].life = particles[MAX_PARTICLES - 15 + i].maxLife;
        
        // Ukuran kecil untuk spark
        particles[MAX_PARTICLES - 15 + i].size = 1.5;
        
        // Warna putih/kuning terang untuk spark
        particles[MAX_PARTICLES - 15 + i].color = (Color){255, 255, 200, 255};
    }
}