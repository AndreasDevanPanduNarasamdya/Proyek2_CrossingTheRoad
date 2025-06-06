#include "../header.h"

// Variabel global untuk modul partikel


void NextLevel(Camera2D *camera, Player *player, Checkpoint *Home, HealthHP *Health, PointsXP *Points, EggyPoints *Egg) {
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
    InitGame(Home, Health, Points, Egg);
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
    Texture2D Blood = LoadTexture("Assets/sprite/blood.png");
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (particles[i].life > 0) {
            // Warna partikel dengan efek fade-out: opacity tergantung pada life
            //Color particleColor = (Color){255, 50, 50, particles[i].life * 8};
            //DrawCircle((int)particles[i].pos.x, (int)particles[i].pos.y, 3, WHITE);
            DrawTextureEx(Blood, (Vector2){particles[i].pos.x, particles[i].pos.y}, 0, 0.25f, WHITE);
        }
    }
}

// Array terpisah untuk partikel checkpoint (opsional)
// Atau bisa menggunakan array particles yang sama dengan flag berbeda

void InitCheckpointParticles(Vector2 checkpointPos) {
    for (int i = 0; i < MAX_CHECKPOINT_PARTICLES; i++) {
        checkpointParticles[i].pos = checkpointPos;

        // Kecepatan acak di X dan Y, cukup untuk efek sebar
        checkpointParticles[i].speed.x = GetRandomValue(-30, 30) / 10.0f;
        checkpointParticles[i].speed.y = GetRandomValue(-30, 30) / 10.0f;

        checkpointParticles[i].life = GetRandomValue(40, 60);
        checkpointParticles[i].size = GetRandomValue(2, 4);

        // Warna tetap terang dan menyala
        checkpointParticles[i].color = (Color){255, 230, 100, 255};
    }
}

void UpdateCheckpointParticles() {
    for (int i = 0; i < MAX_CHECKPOINT_PARTICLES; i++) {
        if (checkpointParticles[i].life > 0) {
            checkpointParticles[i].pos.x += checkpointParticles[i].speed.x;
            checkpointParticles[i].pos.y += checkpointParticles[i].speed.y;

            // Peredam kecepatan ringan
            checkpointParticles[i].speed.x *= 0.95f;
            checkpointParticles[i].speed.y *= 0.95f;

            checkpointParticles[i].life--;
        }
    }
}

void DrawCheckpointParticles() {
    for (int i = 0; i < MAX_CHECKPOINT_PARTICLES; i++) {
        if (checkpointParticles[i].life > 0) {
            float alphaRatio = (float)checkpointParticles[i].life / 60.0f;
            Color fade = checkpointParticles[i].color;
            fade.a = (int)(255 * alphaRatio);

            DrawCircleV(checkpointParticles[i].pos, checkpointParticles[i].size, fade);
        }
    }
}

// Menghitung progress pemain dalam persentase (0.0 - 1.0)
float CalculateProgress(Player *player, int finishY) {
    float totalDistance = (float)(finishY - START_Y); // Misal START_Y = posisi awal player
    float playerDistance = (float)(player->y - START_Y);

    float progress = playerDistance / totalDistance;
    if (progress > 1.0f) progress = 1.0f;
    if (progress < 0.0f) progress = 0.0f;
    return progress;
}

// Menggambar progress bar di layar
void DrawProgressBar(float progress) {
    int barWidth = 20;  
    int barHeight = 200; 
    int padding = 10;  
    int barX = SCREEN_WIDTH - barWidth - padding;
    int barY = (SCREEN_HEIGHT - barHeight) / 2;
    DrawRectangle(barX, barY, barWidth, barHeight, GRAY);
    int fillHeight = (int)(barHeight * progress);
    int fillY = (barY + barHeight) - fillHeight;
    DrawRectangle(barX, fillY, barWidth, fillHeight, RED);
    DrawRectangleLines(barX, barY, barWidth, barHeight, DARKGRAY);
}
