#include <windows.h>
#include <stdio.h>

int main() {
    // Open an audio file (change "example.wav" to "example.mp3" for MP3)
    if (mciSendString("open \"car#1.wav\" type waveaudio alias sound1", NULL, 0, NULL) != 0) {
        printf("Failed to open audio file.\n");
        return 1;
    }

    // Play the audio file
    if (mciSendString("play sound1", NULL, 0, NULL) != 0) {
        printf("Failed to play audio.\n");
        return 1;
    }

    printf("Playing sound... Press Enter to stop.\n");
    getchar(); // Wait for user input to stop playback

    // Close the audio file
    mciSendString("close sound1", NULL, 0, NULL);

    return 0;
}
