#include "sfx.h"
#include <stdio.h>

// Static Sound Variables
static Music backgroundMusic1, menuSound;
static Sound moveChar, getHealth, getCheckpoint, pausedSound, carSound;

void InitSounds()
{
    // Initialize the audio device (required for playing any audio)
    InitAudioDevice();
    if (!IsAudioDeviceReady()) {
        TraceLog(LOG_ERROR, "Audio device initialization failed!");
        return;
    }

    // Load audio files and check for errors
    menuSound = LoadMusicStream("../../sound/menu.wav");
    backgroundMusic1 = LoadMusicStream("../../sound/background5.wav");

    moveChar = LoadSound("../../sound/moveChar.wav");
    getHealth = LoadSound("../../sound/getHealth.wav");
    getCheckpoint = LoadSound("../../sound/getCheckpoint.wav");
    pausedSound = LoadSound("../../sound/pause.wav");
    carSound = LoadSound("../../sound/car.wav");

    // Set initial volume levels
    SetMusicVolume(menuSound, 1.0f);
    SetMusicVolume(backgroundMusic1, 1.0f);
    SetSoundVolume(moveChar, 1.0f);
    SetSoundVolume(getHealth, 1.0f);
    SetSoundVolume(getCheckpoint, 1.0f);
    SetSoundVolume(pausedSound, 1.0f);
    SetSoundVolume(carSound, 1.0f);

    // Play the menu sound as the default background music
    PlayMusicStream(menuSound);
}

void PlayMenuBacksound()
{
    if (!IsMusicStreamPlaying(menuSound))
    {
        PlayMusicStream(menuSound);
    }
    UpdateMusicStream(menuSound);
}

void PlayBackgroundMusic1()
{
    if (!IsMusicStreamPlaying(backgroundMusic1))
    {
        PlayMusicStream(backgroundMusic1);
    }
    UpdateMusicStream(backgroundMusic1);
}

void PlayMoveChar()
{
    PlaySound(moveChar);
}

void PlayGetHealth()
{
    PlaySound(getHealth);
}

void PlayGetCheckpoint()
{
    PlaySound(getCheckpoint);
}

void PlayPausedSound()
{
    PlaySound(pausedSound);
}

void PlayCarSound()
{
    PlaySound(carSound);
}

void UnloadSounds()
{
    StopMusicStream(menuSound);
    StopMusicStream(backgroundMusic1);

    UnloadMusicStream(menuSound);
    UnloadMusicStream(backgroundMusic1);
    UnloadSound(moveChar);
    UnloadSound(getHealth);
    UnloadSound(getCheckpoint);
    UnloadSound(pausedSound);
    UnloadSound(carSound);

    CloseAudioDevice();
}
