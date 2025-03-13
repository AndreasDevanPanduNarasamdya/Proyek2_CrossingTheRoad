#include "sound.h"

// Declare global variables for sound effects
static Music backgroundMusic;
static Sound moveSound;

void InitSounds() {
    InitAudioDevice(); // Initialize the audio device

    // Load background music and movement sound effect
    backgroundMusic = LoadMusicStream("Assets/sound/backsound4.wav");
    moveSound = LoadSound("Assets/sound/sfx_movement.wav");

    PlayMusicStream(backgroundMusic);
}

void PlayBackgroundMusic() {
    UpdateMusicStream(backgroundMusic);
}

void PlayMoveSound() {
    PlaySound(moveSound); // Play the movement sound effect
}


void UnloadSounds() {
    StopMusicStream(backgroundMusic);
    UnloadMusicStream(backgroundMusic);

    // Unload move sound and close audio device
    UnloadSound(moveSound);
    CloseAudioDevice();
}
