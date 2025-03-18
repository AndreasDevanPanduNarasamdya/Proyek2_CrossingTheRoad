#include "sfx.h"
#include <stdio.h>

// Static Sound Variables
Music backgroundMusic1, menuSound;
Sound moveChar, getHealth, getCheckpoint, pausedSound, carSound;

void InitSounds() {
    // Inisialisasi perangkat audio
    InitAudioDevice();
    if (!IsAudioDeviceReady()) {
        TraceLog(LOG_ERROR, "Audio device initialization failed!");
        return;
    }

    // Memuat musik
    menuSound = LoadMusicStream("../sound/backsound4.wav");
    backgroundMusic1 = LoadMusicStream("../sound/backsound4.wav");

    // Memuat efek suara
    moveChar = LoadSound("../../sound/moveChar.wav");
    getHealth = LoadSound("../../sound/getHealth.wav");
    getCheckpoint = LoadSound("../../sound/getCheckpoint.wav");
    pausedSound = LoadSound("../../sound/pause.wav");
    carSound = LoadSound("../../sound/car.wav");

    // Pengaturan volume default
    SetMusicVolume(menuSound, 1.0f);
    SetMusicVolume(backgroundMusic1, 1.0f);
    SetSoundVolume(moveChar, 1.0f);
    SetSoundVolume(getHealth, 1.0f);
    SetSoundVolume(getCheckpoint, 1.0f);
    SetSoundVolume(pausedSound, 1.0f);
    SetSoundVolume(carSound, 1.0f);

    // Memulai musik menu
    PlayMusicStream(menuSound);
}

void UpdateVolume(float volume) {
    // Mengatur volume untuk musik dan semua efek suara
    SetMusicVolume(menuSound, volume);
    SetMusicVolume(backgroundMusic1, volume);
    SetSoundVolume(moveChar, volume);
    SetSoundVolume(getHealth, volume);
    SetSoundVolume(getCheckpoint, volume);
    SetSoundVolume(pausedSound, volume);
    SetSoundVolume(carSound, volume);
}

void PlayMenuBacksound() {
    // Memutar ulang musik jika belum dimainkan
    if (!IsMusicStreamPlaying(menuSound)) {
        PlayMusicStream(menuSound);
    }
    UpdateMusicStream(menuSound);
}

void PlayBackgroundMusic1() {
    // Memutar ulang musik latar jika belum dimainkan
    if (!IsMusicStreamPlaying(backgroundMusic1)) {
        PlayMusicStream(backgroundMusic1);
    }
    UpdateMusicStream(backgroundMusic1);
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

void UnloadSounds() {
    // Berhenti memutar musik
    StopMusicStream(menuSound);
    StopMusicStream(backgroundMusic1);

    // Melepas musik dan efek suara
    UnloadMusicStream(menuSound);
    UnloadMusicStream(backgroundMusic1);
    UnloadSound(moveChar);
    UnloadSound(getHealth);
    UnloadSound(getCheckpoint);
    UnloadSound(pausedSound);
    UnloadSound(carSound);

    // Menutup perangkat audio
    CloseAudioDevice();
}
