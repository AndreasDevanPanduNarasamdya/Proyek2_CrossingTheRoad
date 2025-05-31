#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

void LoadAllSounds();
void UnloadAllSounds();

// Fungsi untuk suara menu
void menusound();
void PlayMenuBacksound();
void StopMenuBacksound();

// Fungsi untuk suara di dalam game
void eggSound();
void PlayBackgroundMusic1();
void UpdateBackgroundMusic();
void StopBacksound1();
void SoundGameover();
void PlayPlayerMoveSound();
void PlayCheckpointSound();
void PlayHealthUpSound();
void PlayPointsSound();
void PlayNabrak();

#endif // SOUND_MANAGER_H