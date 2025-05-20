#include "../header.h"
Sound menuMoveSound, carSound, moveCharSound, nabrak, lose, checkpointSound, healthUpSound, pointsSound;
Music backgroundMusic1, menuBacksound;

// Fungsi untuk memuat semua suara dan musik
void LoadAllSounds() {
    menuMoveSound = LoadSound("Assets/sound/moveChar.wav");
    menuBacksound = LoadMusicStream("Assets/sound/menusound.wav"); 
    backgroundMusic1 = LoadMusicStream("Assets/sound/backsound5.wav"); 
    nabrak = LoadSound("Assets/sound/nabrak.wav");
    carSound = LoadSound("Assets/sound/car1.wav");
    lose = LoadSound("Assets/sound/gameover.wav");
    checkpointSound = LoadSound("Assets/sound/result.wav");
    healthUpSound = LoadSound("Assets/sound/health.wav");
    pointsSound = LoadSound("Assets/sound/point.wav");
    volume = (volume < 0.0f) ? 0.0f : (volume > 1.0f) ? 1.0f : volume;
}

void UnloadAllSounds() {
    UnloadSound(menuMoveSound); 
    UnloadMusicStream(menuBacksound); 
    UnloadMusicStream(backgroundMusic1); 
    UnloadSound(carSound); 
    UnloadSound(moveCharSound); 
    UnloadSound(nabrak);
    UnloadSound(lose);
    UnloadSound(checkpointSound);
    UnloadSound(healthUpSound);
    UnloadSound(pointsSound);
}

// MENU
void menusound() {
    PlaySound(menuMoveSound);
}

void PlayMenuBacksound() {
    PlayMusicStream(menuBacksound); // Memainkan musik backsound menu
    SetMusicVolume(menuBacksound, 1.0f); // Atur volume (opsional)
}

void StopMenuBacksound() {
    StopMusicStream(menuBacksound); // Menghentikan musik backsound menu
}

// BACKSOUND GAME
void PlayBackgroundMusic1() {
    PlayMusicStream(backgroundMusic1); // Memainkan musik backsound level 1
    SetMusicVolume(backgroundMusic1, 1.0f); // Atur volume (opsional)
}

void UpdateBackgroundMusic() {
    UpdateMusicStream(backgroundMusic1); // Memperbarui stream musik
}

void StopBacksound1() {
    StopMusicStream(backgroundMusic1); // Menghentikan musik backsound level 1
}

// GAME SOUND
void SoundGameover() {
    PlaySound(lose);
}

// Car Sound
void CarSound() {
    PlaySound(carSound);
}

// Fungsi untuk memanggil suara ketika pemain bergerak
void PlayPlayerMoveSound() {
    PlaySound(moveCharSound);
}

// Fungsi untuk memanggil suara ketika mendapatkan checkpoint
void PlayCheckpointSound() {
    PlaySound(checkpointSound);
}

// Fungsi untuk memanggil suara ketika mendapatkan health
void PlayHealthUpSound() {
    PlaySound(healthUpSound);
}

// Fungsi untuk memanggil suara ketika mendapatkan point
void PlayPointsSound() {
    PlaySound(pointsSound);
}

// Fungsi helper untuk mengatur volume suara berdasarkan jarak
float CalculateVolumeByDistance(Vector2 source, Vector2 listener, float maxDistance) {
    float distance = CalculateDistance(source, listener);
    float volume = 1.0f - (distance / maxDistance);
    return (volume < 0.0f) ? 0.0f : volume;
}
float CalculateDistance(Vector2 a, Vector2 b)
{
    return sqrtf(powf(b.x - a.x, 2) + powf(b.y - a.y, 2));
}