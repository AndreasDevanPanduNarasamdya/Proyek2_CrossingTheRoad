#include "../header.h"

// Static sound effect variables
Sound moveChar, getHealth, getCheckpoint, pausedSound, carSound;

void InitSounds() {
    InitAudioDevice();
    if (!IsAudioDeviceReady()) {
        TraceLog(LOG_ERROR, "Audio device initialization failed!");
        return;
    }

    // Load sound effects
    moveChar = LoadSound("sound/moveChar.wav");
    getHealth = LoadSound("sound/getHealth.wav");
    getCheckpoint = LoadSound("sound/getCheckpoint.wav");
    pausedSound = LoadSound("sound/pause.wav");
    carSound = LoadSound("sound/car.wav");

    // Set default sound volume
    SetSoundVolume(moveChar, 1.0f);
    SetSoundVolume(getHealth, 1.0f);
    SetSoundVolume(getCheckpoint, 1.0f);
    SetSoundVolume(pausedSound, 1.0f);
    SetSoundVolume(carSound, 1.0f);
}

void PlayMoveChar() {
    PlaySound(moveChar);
}

void PlayGetHealth() {
    PlaySound(getHealth);
}

void PlayGetCheckpoint() {
    PlaySound(getCheckpoint);
}

void PlayPausedSound() {
    PlaySound(pausedSound);
}

void PlayCarSound() {
    PlaySound(carSound);
}

void UpdateVolume(float volume) {
    SetSoundVolume(moveChar, volume);
    SetSoundVolume(getHealth, volume);
    SetSoundVolume(getCheckpoint, volume);
    SetSoundVolume(pausedSound, volume);
    SetSoundVolume(carSound, volume);
}

void UnloadSounds() {
    UnloadSound(moveChar);
    UnloadSound(getHealth);
    UnloadSound(getCheckpoint);
    UnloadSound(pausedSound);
    UnloadSound(carSound);
    CloseAudioDevice();
}
