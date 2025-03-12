#include "sfx.h"

SoundManager CreateSoundManager(const char *soundFilePath) {
    SoundManager manager;
    manager.soundFilePath = soundFilePath;
    manager.sound = LoadSound(soundFilePath);
    return manager;
}

void PlaySoundManager(SoundManager *manager) {
    PlaySound(manager->sound);
}

void UnloadSoundManager(SoundManager *manager) {
    UnloadSound(manager->sound);
}
