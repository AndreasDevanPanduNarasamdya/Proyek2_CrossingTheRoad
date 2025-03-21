#ifndef SFX_H
#define SFX_H

#include "../raylib.h"

// Function prototypes for sounds
void InitSounds();
void PlayMoveChar();
void PlayGetHealth();
void PlayGetCheckpoint();
void PlayPausedSound();
void PlayCarSound();
void UpdateSoundVolume(float volume); // Updated name for clarity
void UnloadSounds();

// Function prototypes for music
void InitMusic(); // Updated name
void PlayMenuBacksound();
void PlayBackgroundMusic1();
void UpdateMusicVolume(float volume); // Updated name
void UnloadMusic(); // Updated name

// Declare static variables for music and sound effects
extern Music backgroundMusic1, menuSound;
extern Sound moveChar, getHealth, getCheckpoint, pausedSound, carSound;

#endif // SFX_H
