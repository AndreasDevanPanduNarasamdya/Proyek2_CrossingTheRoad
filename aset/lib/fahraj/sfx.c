#include <stdio.h>
#include "sound.h"

static Music backgroundMusic, menuBacksound;
static Sound moveSound;

void InitSounds()
{
    InitAudioDevice(); 
    menuBacksound = LoadMusicStream("../../sound/backsound5.wav");
    backgroundMusic = LoadMusicStream("../../sound/backsound4.wav");
    moveSound = LoadSound("../../sound/sfx_movement.wav");

    PlayMusicStream(backgroundMusic);
}

void PlayBackgroundMusic()
{
    UpdateMusicStream(backgroundMusic);
}

void PlayMenuBacksound()
{
    // Play or update the menu backsound
    if (!IsMusicStreamPlaying(menuBacksound))
    {
        PlayMusicStream(menuBacksound); 
    }
    UpdateMusicStream(menuBacksound);
}

void PlayMoveSound()
{
    PlaySound(moveSound);
}
void UnloadSounds()
{
    StopMusicStream(menuBacksound);
    StopMusicStream(backgroundMusic);

    UnloadMusicStream(menuBacksound);
    UnloadMusicStream(backgroundMusic);

    UnloadSound(moveSound);
    CloseAudioDevice();
}