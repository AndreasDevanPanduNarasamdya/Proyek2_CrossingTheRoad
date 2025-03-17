#ifndef SOUND_H
#define SOUND_H

#include "../raylib.h"

// GLOBAL
void CleanUp();

// BACKSOUND 1
void InitBacksound1();
void PlayBacksound1();
void UpdateBacksound1();
void StopBacksound1();
void UnloadBacksound1();

// MOVECHAR
void InitMoveChar();
void PlayMoveChar();
void UnloadMoveChar();

#endif
