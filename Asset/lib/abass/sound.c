#include "raylib.h"
#include "sound.h"

// GLOBAL
void CleanUp()
{
    UnloadMoveChar();
    UnloadBacksound1();
    CloseAudioDevice(); 
}

// BACKSOUND
Music backsound1;
void InitBacksound1()
{
    // Load background music file
    backsound1 = LoadMusicStream("../../sound/backsound5.wav");
    SetMusicVolume(backsound1, 0.5f); // Set volume to 50%
}
void PlayBacksound1()
{
    PlayMusicStream(backsound1);
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

// MOVECHAR
Sound moveChar;
void InitMoveChar()
{
    // Load the sound file for move character
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

// INIT SOUNDS (Unified Initialization)
void InitSounds()
{
    InitAudioDevice(); // Initialize the audio device (required for sound to work)

    // Initialize specific sound components
    InitBacksound1();
    InitMoveChar();
}
