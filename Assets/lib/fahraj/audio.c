#include "../header.h"
Sound menuMoveSound, moveCharSound, nabrak, egg, horn, lose, checkpointSound, healthUpSound, point;
Music backgroundMusic, menuBacksound, loading;
// Fungsi untuk memuat semua suara dan musik
void LoadAllSounds()
{
    // Char
    moveCharSound = LoadSound("Assets/sound/charMove.wav");

    // Menu
    menuMoveSound = LoadSound("Assets/sound/menu_selection.wav");
    menuBacksound = LoadMusicStream("Assets/sound/menusound.wav");

    // Background
    backgroundMusic = LoadMusicStream("Assets/sound/backsound.wav");

    // Loading
    loading = LoadMusicStream("Assets/sound/loading.wav");

    // Car
    horn = LoadSound("Assets/sound/carhorn.wav");
    nabrak = LoadSound("Assets/sound/nabrak.wav");

    // Game
    lose = LoadSound("Assets/sound/gameover.wav");
    egg = LoadSound("Assets/sound/egg.wav");
    checkpointSound = LoadSound("Assets/sound/checkpoint.wav");
    healthUpSound = LoadSound("Assets/sound/health.wav");
    point = LoadSound("Assets/sound/poin.wav");
}

void UnloadAllSounds()
{
    UnloadSound(menuMoveSound);
    UnloadMusicStream(menuBacksound);
    UnloadMusicStream(backgroundMusic);
    UnloadSound(horn);
    UnloadSound(moveCharSound);
    UnloadSound(nabrak);
    UnloadSound(lose);
    UnloadSound(egg);
    UnloadSound(checkpointSound);
    UnloadSound(healthUpSound);
    UnloadSound(point);
}

// MENU
void menusound()
{
    PlaySound(menuMoveSound);
}
void PlayMenuBacksound()
{
    PlayMusicStream(menuBacksound);
    SetMusicVolume(menuBacksound, 1.0f);
}
void StopMenuBacksound()
{
    StopMusicStream(menuBacksound);
}

// Fungsi Loading
void LoadingMusic()
{
    PlayMusicStream(loading);
    SetMusicVolume(loading, 1.0f);
}
void UpdateLoadingMusic()
{
    UpdateMusicStream(loading);
}
void StopLoadingMusic()
{
    StopMusicStream(loading);
}

// BACKSOUND GAME
void PlayBackgroundMusic()
{
    PlayMusicStream(backgroundMusic);
    SetMusicVolume(backgroundMusic, 1.0f);
}
void UpdateBackgroundMusic()
{
    UpdateMusicStream(backgroundMusic);
}
void StopBacksound1()
{
    StopMusicStream(backgroundMusic);
}

// GAME SOUND
void SoundGameover()
{
    PlaySound(lose);
}

void eggSound()
{
    PlaySound(egg);
}

// Fungsi untuk memanggil suara ketika pemain bergerak
void PlayPlayerMoveSound()
{
    PlaySound(moveCharSound);
}

// Fungsi untuk memanggil suara ketika mendapatkan checkpoint
void PlayCheckpointSound()
{
    PlaySound(checkpointSound);
}

// Fungsi untuk memanggil suara ketika mendapatkan health
void PlayHealthUpSound()
{
    PlaySound(healthUpSound);
}

// Fungsi untuk memanggil suara ketika mendapatkan point
void pointSound()
{
    PlaySound(point);
}

// Fungsi untuk memanggil suara ketika terjadi tabrakan
void PlayNabrak()
{
    PlaySound(horn);
    PlaySound(nabrak);
}