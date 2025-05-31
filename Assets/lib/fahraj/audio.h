#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

void LoadAllSounds();
void UnloadAllSounds();

// Fungsi untuk suara menu
void menusound();
void PlayMenuBacksound();
void StopMenuBacksound();

// Fungsi Backsound
void PlayBackgroundMusic();
void UpdateBackgroundMusic();

// Fungsi untuk suara di dalam game
void eggSound();
void StopBacksound1();
void SoundGameover();
void PlayPlayerMoveSound();
void PlayCheckpointSound();
void PlayHealthUpSound();
void PlayPointsSound();
void PlayNabrak();

#endif 