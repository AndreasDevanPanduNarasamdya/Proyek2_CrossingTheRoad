#include "sfx.h"
#include <stdio.h>

// Static music variables
Music backgroundMusic1, menuSound;

void InitMusic() { // Renamed to InitMusic
    InitAudioDevice();
    if (!IsAudioDeviceReady()) {
        TraceLog(LOG_ERROR, "Audio device initialization failed!");
        return;
    }

    // Load music
    menuSound = LoadMusicStream("sound/backsound4.wav");
    backgroundMusic1 = LoadMusicStream("sound/backsound4.wav");

    // Set default music volume
    SetMusicVolume(menuSound, 1.0f);
    SetMusicVolume(backgroundMusic1, 1.0f);

    PlayMusicStream(menuSound); // Start playing menu music
}

void UpdateMusicVolume(float volume) { // Renamed to UpdateMusicVolume
    SetMusicVolume(menuSound, volume);
    SetMusicVolume(backgroundMusic1, volume);
}

void UnloadMusic() { // Renamed to UnloadMusic
    StopMusicStream(menuSound);
    StopMusicStream(backgroundMusic1);

    UnloadMusicStream(menuSound);
    UnloadMusicStream(backgroundMusic1);

    CloseAudioDevice();
}

void PlayMenuBacksound() {
    if (!IsMusicStreamPlaying(menuSound)) {
        PlayMusicStream(menuSound);
    }
    UpdateMusicStream(menuSound);
}

void PlayBackgroundMusic1() {
    if (!IsMusicStreamPlaying(backgroundMusic1)) {
        PlayMusicStream(backgroundMusic1);
    }
    UpdateMusicStream(backgroundMusic1);
}
