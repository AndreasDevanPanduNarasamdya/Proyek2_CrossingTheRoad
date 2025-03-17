#include "sound.h"


Music backsound1;       // Background music for the game
Music menuBacksound;    // Background music for the menu
Sound moveChar;         // Movement sound effect

// Unified Cleanup
void CleanUp()
{
    UnloadMoveChar();
    UnloadBacksound1();
    UnloadMenuBacksound();
    CloseAudioDevice(); 
}

void InitBacksound1()
{
    backsound1 = LoadMusicStream("../../sound/backsound4.wav");
    SetMusicVolume(backsound1, 0.5f); 
}
void PlayBacksound1()
{
    if (!IsMusicStreamPlaying(backsound1)) 
    {
        PlayMusicStream(backsound1); 
    }
}
void UpdateBacksound1()
{
    UpdateMusicStream(backsound1);
}
void StopBacksound1()
{
    StopMusicStream(backsound1);
}
void UnloadBacksound1()
{
    UnloadMusicStream(backsound1);
}

void InitMoveChar()
{
    moveChar = LoadSound("../../sound/moveChar.wav");
    SetSoundVolume(moveChar, 1.0f); 
}
void PlayMoveChar()
{
    PlaySound(moveChar);
}
void UnloadMoveChar()
{
    UnloadSound(moveChar);
}

// MENU BACKGROUND MUSIC FUNCTIONS
void InitMenuBacksound()
{
    // Load background music file for the menu
    menuBacksound = LoadMusicStream("../../sound/backsound4.wav");
    SetMusicVolume(menuBacksound, 0.5f); // Set volume to 50%
}
void PlayMenuBacksound()
{
    if (!IsMusicStreamPlaying(menuBacksound)) 
    {
        PlayMusicStream(menuBacksound); // Play if not already playing
    }
}
void UpdateMenuBacksound()
{
    UpdateMusicStream(menuBacksound);
}
void StopMenuBacksound()
{
    StopMusicStream(menuBacksound);
}
void UnloadMenuBacksound()
{
    UnloadMusicStream(menuBacksound);
}

// Unified Initialization
void InitSounds()
{
    InitAudioDevice(); 
    InitBacksound1(); 
    InitMenuBacksound(); 
    InitMoveChar();  
}
