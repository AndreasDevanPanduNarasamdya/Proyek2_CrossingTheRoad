#include "raylib.h"
#include "sfx.h"

int main(void) {
    // Initialize the audio device
    InitAudioDevice();

    // Create sound managers for different sound files
    SoundManager sound = CreateSoundManager("backsound1.wav");


    // Play the first sound
    PlaySoundManager(&sound);

    // Wait for the user to press ESC to stop
    while (!IsKeyPressed(KEY_ESCAPE)) {}

    // Unload sounds and close the audio device
    UnloadSoundManager(&sound);

    CloseAudioDevice();

    return 0;
}
