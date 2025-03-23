#ifndef AUDIO_H
#define AUDIO_H

// Function prototypes for sounds
void InitSounds();
void PlayMoveChar();
void PlayGetHealth();
void PlayGetCheckpoint();
void PlayPausedSound();
void PlayCarSound();
void UpdateSoundVolume(float volume); // Updated name for clarity
void UnloadAllSounds();
void LoadAllSounds();

// Function prototypes for music
void InitMusic(); // Updated name
void PlayMenuBacksound();
void StopMenuBacksound();
void PlayBackgroundMusic1();
void UpdateMusicVolume(float volume); // Updated name
void UnloadMusic(); // Updated name

// Declare static variables for music and sound effects
extern Music backgroundMusic1, menuBacksound;

extern Sound moveChar, getHealth, getCheckpoint, pausedSound, carSound;

#endif // SFX_H
