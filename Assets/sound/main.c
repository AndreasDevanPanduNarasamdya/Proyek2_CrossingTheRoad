#include "raylib.h"
#include "sfx.h"

int main(void) {
    // Initialize the audio device
    InitAudioDevice();

    // Create sound managers for different sound files
    SoundManager sound1 = CreateSoundManager("backsound1.wav");
    SoundManager sound2 = CreateSoundManager("backsound2.wav");

    // Play the first sound
    PlaySoundManager(&sound1);

    // Wait for the user to press ESC to stop
    while (!IsKeyPressed(KEY_ESCAPE)) {}

    // Play the second sound
    PlaySoundManager(&sound2);

    // Wait for the user to press ESC to stop
    while (!IsKeyPressed(KEY_ESCAPE)) {}

    // Unload sounds and close the audio device
    UnloadSoundManager(&sound1);
    UnloadSoundManager(&sound2);
    CloseAudioDevice();

    return 0;
}
