#include "../raylib.h"

int main() {
    InitAudioDevice();
    Music backsound1 = LoadMusicStream("../../sound/backsound5.wav");
    SetMusicVolume(backsound1, 1.0f);

    PlayMusicStream(backsound1);

    while (!WindowShouldClose()) {
        UpdateMusicStream(backsound1);
    }

    UnloadMusicStream(backsound1);
    CloseAudioDevice();

    return 0;
}
