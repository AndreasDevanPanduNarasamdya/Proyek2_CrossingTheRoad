#ifndef SOUND_H
#define SOUND_H

#include "../raylib.h"

// Global Variables
extern Music backgroundMusic1;
extern Music menuSound;
extern Sound moveChar;

// Functions Declarations
void InitSounds();         // Initialize all sounds
void PlaymenuSound();      // Play and update menu sound
void PlayBacgroundMusic1(); // Update background music
void PlayMoveSound();      // Play move character sound effect
void UnloadSounds();       // Unload all sounds and close audio system

#endif // SOUND_H
