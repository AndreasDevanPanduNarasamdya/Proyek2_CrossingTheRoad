#include "../header.h"
Sound menuMoveSound, carSound, moveCharSound;
Music backgroundMusic1, menuBacksound;

void LoadAllSounds() {
    menuMoveSound = LoadSound("Assets/lib/fahraj/sound/moveChar.wav");
    menuBacksound = LoadMusicStream("Assets/lib/fahraj/sound/menusound.wav"); 
    carSound = LoadSound("Assets/lib/fahraj/sound/car2.wav"); 
    moveCharSound = LoadSound("Assets/lib/fahraj/sound/moveChar.wav"); 
    backgroundMusic1 = LoadMusicStream("Assets/lib/fahraj/sound/backsound4.wav"); 
}

void UnloadAllSounds() {
    UnloadSound(menuMoveSound); // Unload suara navigasi menu
    UnloadMusicStream(menuBacksound); // Unload musik backsound menu
    UnloadMusicStream(backgroundMusic1); // Unload musik backsound menu
    UnloadSound(carSound); // Unload suara mobil
    UnloadSound(moveCharSound); // Unload suara pergerakan karakter
}

void menusound() {
    PlaySound(menuMoveSound);
}
void PlayMenuBacksound() {
    PlayMusicStream(menuBacksound); // Memainkan musik backsound menu
    SetMusicVolume(menuBacksound, 0.5f); // Atur volume (opsional)
}

void PlayBackgroundMusic1(){
    PlayMusicStream(backgroundMusic1); // Memainkan musik backsound menu
    SetMusicVolume(backgroundMusic1, 0.5f); // Atur volume (opsional)
}

void StopMenuBacksound() {
    StopMusicStream(menuBacksound); // Menghentikan musik backsound menu
}
void StopBacksound1() {
    StopMusicStream(backgroundMusic1); // Menghentikan musik backsound menu
}

void StopCarSound() {
    if (IsSoundPlaying(carSound)) {
        StopSound(carSound);
    }
}