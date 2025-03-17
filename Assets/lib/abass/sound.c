#include "../raylib.h"
#include "sound.h"

// Static variables for sounds
Music backgroundMusic1, menuSound;
Sound moveChar;

void InitSounds()
{
    InitAudioDevice(); // Initialize the audio device (needed for playing sound)

    // Load audio assets
    menuSound = LoadMusicStream("../../sound/menuBacksound.wav"); // Replace with actual menu sound file path
    backgroundMusic1 = LoadMusicStream("../../sound/gameBacksound.wav"); // Replace with actual game sound file path
    moveChar = LoadSound("../../sound/moveChar.wav");
    PlayMusicStream(menuSound);
}

void PlaymenuSound()
{
    if (!IsMusicStreamPlaying(menuSound))
    {
        PlayMusicStream(menuSound); // Start menu sound if it's not already playing
    }
    UpdateMusicStream(menuSound); // Update menu sound for smooth playback
}

void PlayBacgroundMusic1()
{
    UpdateMusicStream(backgroundMusic1); // Update background game music
}

void PlayMoveSound()
{
    PlaySound(moveChar); // Play move sound effect
}

void UnloadSounds()
{
    // Stop and unload all music
    StopMusicStream(menuSound);
    StopMusicStream(backgroundMusic1);

    UnloadMusicStream(menuSound);
    UnloadMusicStream(backgroundMusic1);

    // Unload sound effects
    UnloadSound(moveChar);

    // Close the audio device
    CloseAudioDevice();
}
