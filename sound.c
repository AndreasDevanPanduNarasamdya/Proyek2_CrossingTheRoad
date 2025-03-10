#include "raylib.h"

int main(void)
{
    InitAudioDevice();
    Sound sound = LoadSound("backsound2.wav");
    PlaySound(sound);
    while (!IsKeyPressed(KEY_ESCAPE)) {} // Keep the program running
    UnloadSound(sound);
    CloseAudioDevice();
    return 0;
}
