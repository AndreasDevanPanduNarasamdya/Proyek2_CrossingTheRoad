#include "sound.h"

// Static variables for sounds
Music menuSound;

void InitSounds()
{
    InitAudioDevice(); // Initialize audio device
    menuSound = LoadMusicStream("../../sound/menuBacksound.wav"); 
    SetMusicVolume(menuSound, 0.5f);
    PlayMusicStream(menuSound); 
}

void PlaymenuSound()
{
    UpdateMusicStream(menuSound); // Update the menu sound stream to ensure it loops
}

void UnloadSounds()
{
    StopMusicStream(menuSound); 
    UnloadMusicStream(menuSound); 
    CloseAudioDevice(); 
}