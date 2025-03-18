#ifndef SFX_H
#define SFX_H

#include "../raylib.h"

// Deklarasi variabel audio (musik dan efek suara)
extern Music backgroundMusic1, menuSound;
extern Sound moveChar, getHealth, getCheckpoint, pausedSound, carSound;

// Fungsi inisialisasi audio
void InitSounds();
// Fungsi untuk memperbarui volume suara
void UpdateVolume(float volume);


// Fungsi pemutaran musik
void PlayMenuBacksound();
void PlayBackgroundMusic1();

// Fungsi pemutaran efek suara
void PlayMoveChar();
void PlayGetHealth();
void PlayGetCheckpoint();
void PlayPausedSound();
void PlayCarSound();

// Fungsi untuk membersihkan dan melepas audio
void UnloadSounds();

#endif // SFX_H
