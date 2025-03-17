#include "raylib.h"
#include "sound.h"

// GLOBAL
void CleanUp()
{
    UnloadMoveChar();
    UnloadBacksound1();
}

// BACKSOUND
Music backsound1;
void InitBacksound1()
{
    backsound1 = LoadMusicStream("../../sound/backsound5.wav");
    SetMusicVolume(backsound1, 0.5f);
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
    moveChar = LoadSound("../../sound/moveChar.wav"); // Replace with your actual file path
    SetSoundVolume(moveChar, 1.0f);                   // Set volume to 50%
}
void PlayMoveChar()
{
    PlaySound(moveChar);
}
void UnloadMoveChar()
{
    UnloadSound(moveChar);
}
