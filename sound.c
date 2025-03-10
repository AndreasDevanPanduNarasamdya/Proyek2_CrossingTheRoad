#include "raylib.h"

int main(void)
{
    // Initialize the audio device
    InitAudioDevice();
    
    // Load a sound file
    Sound sound = LoadSound("backsound2.wav"); // Ensure the file is in the same directory
    
    // Start the main loop
    while (!WindowShouldClose()) // This loop is here for illustration; no window is actually created
    {
        if (IsKeyPressed(KEY_SPACE)) // Play sound when SPACE key is pressed
        {
            PlaySound(sound);
        }
    }
    
    // Unload the sound and close the audio device
    UnloadSound(sound);
    CloseAudioDevice();
    
    return 0;
}
