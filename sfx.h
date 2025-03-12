#include "sfx.h"

SoundManager CreateSoundManager(const char* fileName) {
    SoundManager manager;
    manager.sound = LoadSound(fileName);
    return manager;
}

void PlaySoundManager(SoundManager* manager) {
    PlaySound(manager->sound);
}

void UnloadSoundManager(SoundManager* manager) {
    UnloadSound(manager->sound);
}
