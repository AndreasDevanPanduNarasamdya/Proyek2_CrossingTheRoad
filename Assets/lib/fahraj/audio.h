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
void StopBacksound1();

// Fungsi Loading
void LoadingMusic();
void UpdateLoadingMusic();
void StopLoadingMusic();

// Fungsi untuk suara di dalam game
void eggSound();
void StopBacksound1();
void SoundGameover();
void PlayPlayerMoveSound();
void PlayCheckpointSound();
void PlayHealthUpSound();
void pointSound();
void PlayNabrak();

#endif 