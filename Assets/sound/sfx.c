#include <stdio.h>
#include "sfx.h"

// Global variables for sound effect settings
int sound_enabled = 1; // 1 = enabled, 0 = disabled
int volume_level = 100; // Default volume level (0 to 100)

// Function to enable sound effects
void enable_sound_effects() {
    sound_enabled = 1;
    printf("Sound effects enabled.\n");
}

// Function to disable sound effects
void disable_sound_effects() {
    sound_enabled = 0;
    printf("Sound effects disabled.\n");
}

// Function to set volume level
void set_volume(int level) {
    if (level < 0 || level > 100) {
        printf("Invalid volume level. Please enter a value between 0 and 100.\n");
        return;
    }
    volume_level = level;
    printf("Volume level set to %d.\n", volume_level);
}

// Function to simulate playing a sound
void play_sound(const char *sound_name) {
    if (!sound_enabled) {
        printf("Sound effects are disabled. Cannot play sound.\n");
        return;
    }
    printf("Playing sound: %s at volume level %d.\n", sound_name, volume_level);
}
