#include "../raylib.h"
#include "sfx.h"

// Static Sound Variables
static Music backgroundMusic1, menuSound;
static Sound moveChar;

void InitSounds()
{
    InitAudioDevice(); // Initialize the audio device

    // Load audio files
    menuSound = LoadMusicStream("../../sound/backsound4.wav");
    backgroundMusic1 = LoadMusicStream("../../sound/backsound4.wav");
    moveChar = LoadSound("../../sound/moveChar.wav");
    PlayMusicStream(menuSound);
    PlayMusicStream(backgroundMusic1);
}

void PlayMenuBacksound()
{
    // Play or update the menu background sound
    if (!IsMusicStreamPlaying(menuSound))
    {
        PlayMusicStream(menuSound); // Start playing the menu music
    }
    UpdateMusicStream(menuSound); // Update the menu music stream
}

void PlayBackgroundMusic1()
{
    // Keep the background music for the game updated
    UpdateMusicStream(backgroundMusic1);
}

void PlayMoveChar()
{
    PlaySound(moveChar); // Play the move sound effect
}

void UnloadSounds()
{
    // Stop and unload all sounds
    StopMusicStream(menuSound);
    StopMusicStream(backgroundMusic1);

    UnloadMusicStream(menuSound);
    UnloadMusicStream(backgroundMusic1);

    UnloadSound(moveChar);

    CloseAudioDevice(); // Close the audio system
}
