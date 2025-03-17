#ifndef SOUND_H
#define SOUND_H

#include "../raylib.h" // Ensure raylib is included for audio support

// Global Variables
extern Music backsound1;       // Background music for the game
extern Music menuBacksound;    // Background music for the menu
extern Sound moveChar;         // Movement sound effect

// Unified Initialization and Cleanup
void InitSounds();       // Unified initialization of all sounds
void CleanUp();          // Unified cleanup of all sound resources

// Game Background Music Functions
void InitBacksound1();   // Initialize game background music
void PlayBacksound1();   // Start playing game background music
void UpdateBacksound1(); // Update game background music stream
void StopBacksound1();   // Stop game background music
void UnloadBacksound1(); // Unload game background music

// Menu Background Music Functions
void InitMenuBacksound();   // Initialize menu background music
void PlayMenuBacksound();   // Start playing menu background music
void UpdateMenuBacksound(); // Update menu background music stream
void StopMenuBacksound();   // Stop menu background music
void UnloadMenuBacksound(); // Unload menu background music

// Move Character Sound Functions
void InitMoveChar();      // Initialize move character sound effect
void PlayMoveChar();      // Play the move character sound effect
void UnloadMoveChar();    // Unload the move character sound effect

#endif // SOUND_H
