#ifndef SFX_H
#define SFX_H

#include "../raylib.h"

// Function declarations for initializing, playing, and unloading sounds
void InitSounds();
void PlayBackgroundMusic1();
void PlayMenuBacksound();
void PlayMoveChar();
void PlayGetHealth();
void PlayGetCheckpoint();
void PlayPausedSound();
void PlayCarSound(); // "Mobil" in English for consistency
void UnloadSounds();

#endif
