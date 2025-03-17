#include "../raylib.h"
#include "sfx.h"

static Music backgroundMusic, menuBacksound;
static Sound moveSound;

void InitSounds()
{
    InitAudioDevice(); // Initialize the audio device
    menuBacksound = LoadMusicStream("../../sound/backsound4.wav");
    backgroundMusic = LoadMusicStream("../../sound/backsound4.wav");
    moveSound = LoadSound("../../sound/sfx_movement.wav");

    PlayMusicStream(backgroundMusic);
};

void PlayMenuBacksound()
{
    // Play or update the menu backsound
    if (!IsMusicStreamPlaying(menuBacksound))
    {
        PlayMusicStream(menuBacksound); // Start playing the menu backsound if it's not already playing
    }
    UpdateMusicStream(menuBacksound); // Keep the music stream updated
};

void PlayBacgroundMusic()
{
    UpdateMusicStream(backgroundMusic);
};

void PlayMoveSound()
{
    PlaySound(moveSound);
};

void UnloadSounds()
{
    StopMusicStream(menuBacksound);
    StopMusicStream(backgroundMusic);

    UnloadMusicStream(menuBacksound);
    UnloadMusicStream(backgroundMusic);

    UnloadSound(moveSound);
    CloseAudioDevice();
};