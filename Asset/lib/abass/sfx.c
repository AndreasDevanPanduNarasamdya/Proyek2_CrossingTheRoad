#include "../raylib.h"
#include "sfx.h"

static Music backgroundMusic1, menuSound;
static Sound moveChar;

void InitSounds()
{
    InitAudioDevice(); // Initialize the audio device
    menuSound = LoadMusicStream("../../sound/backsound4.wav");
    backgroundMusic1 = LoadMusicStream("../../sound/backsound4.wav");
    moveChar = LoadSound("../../sound/sfx_movement.wav");

    PlayMusicStream(backgroundMusic1);
}

void PlaymenuSound()
{
    // Play or update the menu backsound
    if (!IsMusicStreamPlaying(menuSound))
    {
        PlayMusicStream(menuSound); // Start playing the menu backsound if it's not already playing
    }
    UpdateMusicStream(menuSound); // Keep the music stream updated
}

void PlayBacgroundMusic1()
{
    UpdateMusicStream(backgroundMusic1);
}

void PlaymoveChar()
{
    PlaySound(moveChar);
}

void UnloadSounds()
{
    StopMusicStream(menuSound);
    StopMusicStream(backgroundMusic1);

    UnloadMusicStream(menuSound);
    UnloadMusicStream(backgroundMusic1);

    UnloadSound(moveChar);
    CloseAudioDevice();
}