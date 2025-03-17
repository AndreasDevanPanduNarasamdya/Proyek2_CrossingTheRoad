#include "../raylib.h"
#include "sfx.h"

static Music backgroundMusic, menuBacksound;
static Sound moveChar;

void InitSounds()
{
    InitAudioDevice(); // Initialize the audio device
    menuBacksound = LoadMusicStream("../../sound/backsound4.wav");
    backgroundMusic = LoadMusicStream("../../sound/backsound4.wav");
    moveChar = LoadSound("../../sound/sfx_movement.wav");

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

void PlaymoveChar()
{
    PlaySound(moveChar);
};

void UnloadSounds()
{
    StopMusicStream(menuBacksound);
    StopMusicStream(backgroundMusic);

    UnloadMusicStream(menuBacksound);
    UnloadMusicStream(backgroundMusic);

    UnloadSound(moveChar);
    CloseAudioDevice();
};