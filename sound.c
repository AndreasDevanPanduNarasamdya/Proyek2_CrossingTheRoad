#include "sfx.h"

// Declare a global Music variable for background music
static Music backgroundMusic;

void InitSounds() {
    InitAudioDevice(); // Initialize the audio device
    backgroundMusic = LoadMusicStream("Assets/sound/background2.wav");
    PlayMusicStream(backgroundMusic);
}

void PlayBackgroundMusic() {
    UpdateMusicStream(backgroundMusic);
}

void UnloadSounds() {
    StopMusicStream(backgroundMusic);
    UnloadMusicStream(backgroundMusic);
    CloseAudioDevice(); // Close the audio device
}
