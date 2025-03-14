#include "sound.h"

// Declare global variables for sound effects
static Music backgroundMusic, menuBacksound;
static Sound moveSound;

void InitSounds()
{
    InitAudioDevice(); // Initialize the audio device

    // Load background music and movement sound effect
    menuBacksound = LoadMusicStream("../../sound/backsound4.wav");
    backgroundMusic = LoadMusicStream("../../sound/backsound4.wav");
    moveSound = LoadSound("../../sound/sfx_movement.wav");

    PlayMusicStream(backgroundMusic);
}

void PlayBackgroundMusic()
{
    UpdateMusicStream(backgroundMusic);
}
void PlayMoveSound()
{
    PlaySound(moveSound); // Play the movement sound effect
}
void UnloadSounds()
{
    StopMusicStream(menuBacksound);
    StopMusicStream(backgroundMusic);

    UnloadMusicStream(menuBacksound);
    UnloadMusicStream(backgroundMusic);

    UnloadSound(moveSound);
    CloseAudioDevice(); // Close the audio device
}
