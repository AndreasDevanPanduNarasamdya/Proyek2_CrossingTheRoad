#include "../header.h"
Sound menuMoveSound, carSound, moveCharSound, nabrak, lose, checkpointSound, healthUpSound, pointsSound;
Music backgroundMusic1, menuBacksound;

// Fungsi untuk memuat semua suara dan musik
void LoadAllSounds() {
    menuMoveSound = LoadSound("Assets/sound/moveChar.wav");
    menuBacksound = LoadMusicStream("Assets/sound/menusound.wav"); 
    carSound = LoadSound("Assets/sound/car2.wav"); 
    moveCharSound = LoadSound("Assets/sound/moveChar.wav");
    backgroundMusic1 = LoadMusicStream("Assets/sound/backsound4.wav"); 
    nabrak = LoadSound("Assets/sound/nabrak.wav");
    lose = LoadSound("Assets/sound/gameover.wav");
    checkpointSound = LoadSound("Assets/sound/result.wav");
    healthUpSound = LoadSound("Assets/sound/health.wav");
    pointsSound = LoadSound("Assets/sound/point+.wav");

}
void UnloadAllSounds() {
    UnloadSound(menuMoveSound); 
    UnloadMusicStream(menuBacksound); 
    UnloadMusicStream(backgroundMusic1); 
    UnloadSound(carSound); 
    UnloadSound(moveCharSound); 
    UnloadSound(nabrak);
}

// MENU
void menusound() {
    PlaySound(menuMoveSound);
}
void PlayMenuBacksound() {
    PlayMusicStream(menuBacksound); // Memainkan musik backsound menu
    SetMusicVolume(menuBacksound, 0.5f); // Atur volume (opsional)
}
void StopMenuBacksound() {
    StopMusicStream(menuBacksound); // Menghentikan musik backsound menu
}

// BACKSOUND GAME
void PlayBackgroundMusic1(){
    PlayMusicStream(backgroundMusic1); // Memainkan musik backsound menu
    SetMusicVolume(backgroundMusic1, 0.5f); // Atur volume (opsional)
}
void StopBacksound1() {
    StopMusicStream(backgroundMusic1); // Menghentikan musik backsound menu
}

// GAME SOUND
void StopCarSound() {
    if (IsSoundPlaying(carSound)) {
        StopSound(carSound);
    }
}
void SoundGameover(){

}