#include "../raylib.h"
#include "sfx.h"
#include <stdio.h>

// Static Sound Variables
static Music backgroundMusic1, menuSound;
static Sound moveChar;

void InitSounds()
{
    // Initialize the audio device (required for playing any audio)
    InitAudioDevice();

    // Load audio files and check for errors
    menuSound = LoadMusicStream("../../sound/backsound4.wav");
    if (menuSound.stream.buffer == NULL)
    {
        TraceLog(LOG_WARNING, "Failed to load menu background sound: ../../sound/backsound4.wav");
    }

    backgroundMusic1 = LoadMusicStream("../../sound/backsound4.wav");
    if (backgroundMusic1.stream.buffer == NULL)
    {
        TraceLog(LOG_WARNING, "Failed to load game background music: ../../sound/backsound4.wav");
    }

    moveChar = LoadSound("../../sound/moveChar.wav");
    if (moveChar.stream.buffer == NULL)
    {
        TraceLog(LOG_WARNING, "Failed to load move character sound: ../../sound/moveChar.wav");
    }

    // Set initial volume levels
    SetMusicVolume(menuSound, 1.0f);       // Maximum volume for menu sound
    SetMusicVolume(backgroundMusic1, 1.0f); // Maximum volume for game music
    SetSoundVolume(moveChar, 1.0f);        // Maximum volume for move sound

    // Play only one music stream at a time; do not play both simultaneously
    PlayMusicStream(menuSound); // Start playing the menu sound by default
}

void PlayMenuBacksound()
{
    // Play or update the menu background music
    if (!IsMusicStreamPlaying(menuSound))
    {
        PlayMusicStream(menuSound); // Restart menu music if it is not playing
    }
    UpdateMusicStream(menuSound); // Keep the menu music updated for smooth playback
}

void PlayBackgroundMusic1()
{
    // Play or update the game background music
    if (!IsMusicStreamPlaying(backgroundMusic1))
    {
        PlayMusicStream(backgroundMusic1); // Restart game music if it is not playing
    }
    UpdateMusicStream(backgroundMusic1); // Keep the game music updated for smooth playback
}

void PlayMoveChar()
{
    // Play the movement sound effect
    PlaySound(moveChar);
}

void UnloadSounds()
{
    // Stop all music streams
    StopMusicStream(menuSound);
    StopMusicStream(backgroundMusic1);

    // Unload all music streams and sound effects
    UnloadMusicStream(menuSound);
    UnloadMusicStream(backgroundMusic1);
    UnloadSound(moveChar);

    // Close the audio device to free resources
    CloseAudioDevice();
}
