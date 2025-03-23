#ifndef AUDIO_H
#define AUDIO_H

// Function prototypes for sounds
void UnloadAllSounds();
void LoadAllSounds();
void PlayMenuBacksound();
void StopMenuBacksound();
void PlayBackgroundMusic1();

extern Music backgroundMusic1, menuBacksound;
extern Sound moveChar, getHealth, getCheckpoint, pausedSound, carSound;

#endif // SFX_H
