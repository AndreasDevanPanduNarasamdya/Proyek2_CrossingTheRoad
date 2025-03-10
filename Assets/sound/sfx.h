#ifndef SOUND_H
#define SOUND_H

#include "raylib.h"

// Define a struct to represent a SoundManager
typedef struct {
    Sound sound;
    const char *soundFilePath;
} SoundManager;

// Functions to operate on the SoundManager
SoundManager CreateSoundManager(const char *soundFilePath);
void PlaySoundManager(SoundManager *manager);
void UnloadSoundManager(SoundManager *manager);

#endif
