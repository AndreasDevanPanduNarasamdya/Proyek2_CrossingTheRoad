#include "../header.h"
Sound menuMoveSound, moveCharSound, nabrak, egg, horn, lose, checkpointSound, healthUpSound, pointsSound;
Music backgroundMusic, menuBacksound;
// Fungsi untuk memuat semua suara dan musik
void LoadAllSounds() {
    //Char
    moveCharSound = LoadSound("Assets/sound/charMove.wav");

    //Menu
    menuMoveSound = LoadSound("Assets/sound/menu_selection.wav");
    menuBacksound = LoadMusicStream("Assets/sound/menusound.wav"); 

    //Background
    backgroundMusic = LoadMusicStream("Assets/sound/background.wav"); 
    
    //Car
    horn = LoadSound("Assets/sound/carhorn.wav");
    nabrak = LoadSound("Assets/sound/nabrak.wav");

    //Game
    lose = LoadSound("Assets/sound/gameover.wav");
    egg =  LoadSound("Assets/sound/egg.wav");
    checkpointSound = LoadSound("Assets/sound/checkpoint.wav");
    healthUpSound = LoadSound("Assets/sound/health.wav");
    pointsSound = LoadSound("Assets/sound/point.wav");
}

void UnloadAllSounds() {
    UnloadSound(menuMoveSound); 
    UnloadMusicStream(menuBacksound); 
    UnloadMusicStream(backgroundMusic); 
    UnloadSound(horn); 
    UnloadSound(moveCharSound); 
    UnloadSound(nabrak);
    UnloadSound(lose);
    UnloadSound(egg);
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
    SetMusicVolume(menuBacksound, 1.0f);
}

void StopMenuBacksound() {
    StopMusicStream(menuBacksound); // Menghentikan musik backsound menu
}

// BACKSOUND GAME
void PlayBackgroundMusic1() {
    PlayMusicStream(backgroundMusic); // Memainkan musik backsound
    SetMusicVolume(backgroundMusic, 1.0f);
}

void UpdateBackgroundMusic() {
    UpdateMusicStream(backgroundMusic); // Memperbarui stream musik
}

void StopBacksound1() {
    StopMusicStream(backgroundMusic);
}

// GAME SOUND
void SoundGameover() {
    PlaySound(lose);
}

void eggSound(){
    PlaySound(egg);
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

// Fungsi untuk memanggil suara ketika terjadi tabrakan
void PlayNabrak(){
    PlaySound(horn);
    PlaySound(nabrak);
}