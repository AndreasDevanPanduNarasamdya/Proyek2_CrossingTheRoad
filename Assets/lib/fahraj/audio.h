#ifndef AUDIO_H
#define AUDIO_H

// Fungsi untuk Sound
void UnloadAllSounds();
void LoadAllSounds();
void PlayMenuBacksound();
void StopMenuBacksound();
void PlayBackgroundMusic1();
float CalculateDistance(Vector2 a, Vector2 b);
float CalculateVolumeByDistance(Vector2 source, Vector2 listener, float maxDistance);
#endif // AUDIO