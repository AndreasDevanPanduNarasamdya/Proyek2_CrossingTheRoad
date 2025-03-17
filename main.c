#include "Assets/lib/raylib.h"
#include "Assets/lib/fahraj/sfx.h"

int main() {
    InitAudioDevice(); // Initialize audio device
    InitSounds();      // Load sounds

    while (!WindowShouldClose()) {
        PlayMenuBacksound(); // Play/update menu background sound

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Testing sound system...", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    UnloadSounds();    // Unload all sounds
    CloseAudioDevice(); // Close audio device
    return 0;
}
