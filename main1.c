#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "header.h"

int main() {
    start();
    return 0;
}
Sound menuMoveSound, carSound, moveCharSound;
Music backgroundMusic1, menuBacksound;
int margin = 20;

void LoadAllSounds() {
    menuMoveSound = LoadSound("Assets/lib/fahraj/sound/moveChar.wav");
    menuBacksound = LoadMusicStream("Assets/lib/fahraj/sound/menusound.wav"); 
    carSound = LoadSound("Assets/lib/fahraj/sound/car2.wav"); 
    moveCharSound = LoadSound("Assets/lib/fahraj/sound/moveChar.wav"); 
    backgroundMusic1 = LoadMusicStream("Assets/lib/fahraj/sound/backsound4.wav"); 
}

void UnloadAllSounds() {
    UnloadSound(menuMoveSound); // Unload suara navigasi menu
    UnloadMusicStream(menuBacksound); // Unload musik backsound menu
    UnloadMusicStream(backgroundMusic1); // Unload musik backsound menu
    UnloadSound(carSound); // Unload suara mobil
    UnloadSound(moveCharSound); // Unload suara pergerakan karakter
}

void menusound() {
    PlaySound(menuMoveSound);
}
void PlayMenuBacksound() {
    PlayMusicStream(menuBacksound); // Memainkan musik backsound menu
    SetMusicVolume(menuBacksound, 0.5f); // Atur volume (opsional)
}

void PlayBackgroundMusic1(){
    PlayMusicStream(backgroundMusic1); // Memainkan musik backsound menu
    SetMusicVolume(backgroundMusic1, 0.5f); // Atur volume (opsional)
}

void StopMenuBacksound() {
    StopMusicStream(menuBacksound); // Menghentikan musik backsound menu
}
void StopBacksound1() {
    StopMusicStream(backgroundMusic1); // Menghentikan musik backsound menu
}

void NextLevel(Camera2D *camera, Player *player) {
    // Tingkatkan level
    level++;
    
    // Reset posisi pemain ke tengah bawah grid
    player->x = GRID_WIDTH / 2;
    player->y = GRID_HEIGHT - 2;  // Kurangi 2 agar tidak keluar batas
    
    checkpoint.x = player->x;
    checkpoint.y = player->y;

    // Reset posisi kamera ke awal
    camera->target.y = player->y * CELL_SIZE;
    // Inisialisasi ulang game untuk level baru
    InitGame();
}

void DefineArrayCord()
{
    //int x;
    //int y;
    Vector2 ScreenVector;
    for (ScreenVector.x = 0; ScreenVector.x <= SCREEN_WIDTH; ++ScreenVector.x )
    {
        for (ScreenVector.y = 0; ScreenVector.y <= SCREEN_HEIGHT; ++ScreenVector.y)
        {
            CoordArr[(int)ScreenVector.x][(int)ScreenVector.y] = ScreenVector;
        }
    }
}

void RenderRoads()
{
            DrawTextureEx(background, (Vector2){150,0}, 0.0f, 0.25, WHITE);
}

void RenderCharacter(Texture2D *PlayerSprite, Player player)
{
    DrawTextureEx(*PlayerSprite, (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE}, 0.0f, 0.1f, WHITE);
}

void Renderchkpointtxt() 
{
        DrawTextureEx(checkpointtxt, (Vector2){margin + 240, margin}, 0, 0.2, WHITE);
}

void CheckpointLogic() {
    if (player.score > lastscore) {
        lastscore = player.score;  // Update last score
        showCheckpointText = true;
        checkpointTimer = 300;  // Show for 300 frames (~5 seconds at 60 FPS)
    }
}

void RenderFlags()
{
    DrawTextureEx(checkpointflag, (Vector2){500, 375}, 0.0f, 0.1, WHITE);
    DrawTextureEx(checkpointflag, (Vector2){200, 1650}, 0.0f, 0.1, WHITE);
}

void ResetTimer()
{
    if (passed == true)
    {
        Renderchkpointtxt();
        timer -= GetFrameTime() * 1000;
        if (timer <= 0)
        {
            passed = false;
            timer = 2000;
        }
    }
}

void RenderHealths()
{
    DrawTextureEx(healthup, (Vector2){345, 548}, 0.0f, 0.07, WHITE);
    DrawTextureEx(healthup, (Vector2){478, 1323}, 0.0f, 0.07, WHITE);
}

void RenderPoints()
{
    DrawTextureEx(points, (Vector2){178, 548}, 0.0f, 0.07, WHITE);
    DrawTextureEx(points, (Vector2){267, 1523}, 0.0f, 0.07, WHITE);
}

 void RenderCars(int *numCars, Car cars[])
{
    for (int i = 0; i < *numCars; i++)  // Use *numCars instead of numCars
    {
        int x = cars[i].x * CELL_SIZE;
        int y = cars[i].y * CELL_SIZE;
        Texture2D carTexture;

        if (y != 95 * CELL_SIZE && y != 101 * CELL_SIZE) 
        {
            if (cars[i].type == 0) 
            {
                carTexture = TaxiTexture;
            }
            else if (cars[i].type == 1) 
            {
                carTexture = TruckTexture;
            }  
            else if (cars[i].type == 2)
            {
                carTexture = VanTexture;
            }
            else if (cars[i].type == 3)
            {
                carTexture = Mustang;
            }
        }
        else
        {
            carTexture = logs;
        }
        if (cars[i].direction == 1)
        {
            if (y != 95 * CELL_SIZE && y != 101 * CELL_SIZE)
            {
                DrawTextureEx(carTexture, (Vector2){x,y}, 0.0f, 0.03f, WHITE);
            }
            else
            {
                DrawTextureEx(carTexture, (Vector2){x,y}, 0.0f, 0.1f, WHITE);
            }
        }
        else 
        {
            if (y != 95 * CELL_SIZE && y != 101 * CELL_SIZE)
            {
                DrawTextureEx(carTexture, (Vector2){x,y+40}, 180.0f, 0.03f, WHITE);
            }
            else
            {
                DrawTextureEx(carTexture, (Vector2){x,y+40}, 180.0f, 0.1f, WHITE);
            }
        }
        
    }
}

void UnloadAllTextures()
{
    UnloadTexture(TaxiTexture);
    UnloadTexture(TruckTexture);
    UnloadTexture(VanTexture);
    UnloadTexture(Mustang);
    UnloadTexture(background);
    UnloadTexture(PlayerSprite);
    UnloadTexture(checkpointtxt);
    UnloadTexture(healthup);
}

void LoadAllTextures()
{
    TaxiTexture = LoadTexture("Assets/sprite/taxi.png");
    TruckTexture = LoadTexture("Assets/sprite/gruppesechs_van.png");
    VanTexture = LoadTexture("Assets/sprite/vanbankk.png");
    Mustang = LoadTexture("Assets/sprite/mustang.png");
    PlayerSprite = LoadTexture("Assets/sprite/npcmoment.png");
    background = LoadTexture("Assets/sprite/mapproyek2.png");
    logs = LoadTexture("Assets/sprite/logbridge.png");
    checkpointflag = LoadTexture("Assets/sprite/checkpointflag.png");
    checkpointtxt = LoadTexture("Assets/sprite/checkpointtxt.png");
    healthup = LoadTexture("Assets/sprite/healthpowerup.png");
    points = LoadTexture("Assets/sprite/pointsup.png");
}

void RenderInstructions(Player player, char *coordText, int level)
{

    // Menampilkan teks di sudut kiri atas layar
    DrawText(TextFormat("Score: %d", player.score), margin, margin, 20, WHITE);
    DrawText(TextFormat("Lives: %d", player.lives), margin, margin + 30, 20, WHITE);
    DrawText(TextFormat("Level: %d", level), margin, margin + 60, 20, WHITE);
    DrawText(coordText, margin, margin + 90, 20, WHITE);
    DrawText("Use Arrow Keys to Move", margin, margin + 120, 20, WHITE);
    DrawText(TextFormat("health: %d", health_upgrade), margin, margin + 150, 20, WHITE);
}

MenuOption ShowMenu() {
    int selectedOption = 0;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    const char *menuOptions[] = {"Start Game", "Options", "Exit"};
    int totalOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);

    // Mainkan backsound menu jika belum diputar
    if (!IsMusicStreamPlaying(menuBacksound)) {
        PlayMenuBacksound();
    }

    while (!WindowShouldClose()) {
        UpdateMusicStream(menuBacksound); // Update musik backsound setiap frame

        BeginDrawing();
        ClearBackground(RAYWHITE);
         int titleWidth = MeasureText("Crossing The Road", 40);
        DrawText("Crossing The Road", (screenWidth - titleWidth) / 2, screenHeight / 4, 40, DARKGRAY);


        // Draw menu options
        for (int i = 0; i < totalOptions; i++) {
            int textWidth = MeasureText(menuOptions[i], 30);
            int posX = (GetScreenWidth() - textWidth) / 2;
            int posY = (GetScreenHeight() / 2) + i * 50;

            Color textColor = (i == selectedOption) ? WHITE : BLACK;

            if (i == selectedOption) {
                DrawRectangle(posX - 10, posY - 5, textWidth + 20, 40, RED);
            }

            DrawText(menuOptions[i], posX, posY, 30, textColor);
        }

        EndDrawing();

        // Handle input
        if (IsKeyPressed(KEY_DOWN)) {
            selectedOption = (selectedOption + 1) % totalOptions; // Move selection down
            menusound(); // Mainkan suara navigasi menu
        }
        if (IsKeyPressed(KEY_UP)) {
            selectedOption = (selectedOption - 1 + totalOptions) % totalOptions; // Move selection up
            menusound(); // Mainkan suara navigasi menu
        }
        if (IsKeyPressed(KEY_ENTER)) {
            if (selectedOption == 1) { // Jika memilih Options
                isInMainMenu = true; // Tetap di menu utama
                return MENU_OPTIONS;
            }
            return (MenuOption)selectedOption;
        }
    }

    return MENU_EXIT;
}

void ShowOptions(float *volume, bool *isFullscreen) {
    int selectedOption = 0;

    while (!WindowShouldClose()) {
        UpdateMusicStream(menuBacksound); 

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Options", SCREEN_WIDTH / 2 - MeasureText("Options", 30) / 2, 50, 30, DARKGRAY);
        DrawText(TextFormat("Volume: %d%%", (int)(*volume * 100)), 100, 120, 20, selectedOption == 0 ? RED : BLACK);
        DrawText(TextFormat("Fullscreen: %s", *isFullscreen ? "ON" : "OFF"), 100, 150, 20, selectedOption == 1 ? RED : BLACK);
        DrawText("Back", 100, 180, 20, selectedOption == 2 ? RED : BLACK);

        EndDrawing();

        // Navigasi menu
        if (IsKeyPressed(KEY_DOWN)) selectedOption = (selectedOption + 1) % 3;
        if (IsKeyPressed(KEY_UP)) selectedOption = (selectedOption - 1 + 3) % 3;

        // Perubahan volume langsung bekerja
        if (selectedOption == 0) {
            if (IsKeyDown(KEY_LEFT) && *volume > 0.0f) {
                *volume -= 0.01f; // Kurangi volume lebih halus
                if (*volume < 0.0f) *volume = 0.0f;
            }
            if (IsKeyDown(KEY_RIGHT) && *volume < 1.0f) {
                *volume += 0.01f; // Tambah volume lebih halus
                if (*volume > 1.0f) *volume = 1.0f;
            }
            SetMasterVolume(*volume); // Terapkan perubahan volume
        }

        // Enter digunakan untuk memilih opsi
        if (IsKeyPressed(KEY_ENTER)) {
            if (selectedOption == 1) { // Toggle fullscreen
                *isFullscreen = !(*isFullscreen);
                ToggleFullscreen();
            } else if (selectedOption == 2) { // Kembali ke menu utama
                return;
            }
        }
    }
}

void ShowTryAgain(bool *restartGame) {
    int selectedOption = 0;
    const char *options[] = {"Try Again", "Main Menu"};
    int totalOptions = 2;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Game Over", SCREEN_WIDTH / 2 - MeasureText("Game Over", 40) / 2, SCREEN_HEIGHT / 4, 40, RED);

        for (int i = 0; i < totalOptions; i++) {
            int textWidth = MeasureText(options[i], 30);
            int posX = (SCREEN_WIDTH - textWidth) / 2;
            int posY = (SCREEN_HEIGHT / 2) + i * 50;

            Color textColor = (i == selectedOption) ? WHITE : BLACK;

            if (i == selectedOption) {
                DrawRectangle(posX - 10, posY - 5, textWidth + 20, 40, RED);
            }

            DrawText(options[i], posX, posY, 30, textColor);
        }

        EndDrawing();

        if (IsKeyPressed(KEY_DOWN)) selectedOption = (selectedOption + 1) % totalOptions;
        if (IsKeyPressed(KEY_UP)) selectedOption = (selectedOption - 1 + totalOptions) % totalOptions;
        if (IsKeyPressed(KEY_ENTER)) {
            if (selectedOption == 0) {  // Try Again
                *restartGame = true;
                return;
            } else if (selectedOption == 1) {  // Main Menu
                *restartGame = false;
                return;
            }
        }
    }
}

void HandleGameOver(bool *kalah, bool *PermainanBerakhir) {
    printf("HandleGameOver() DIPANGGIL! Game Over terjadi!\n");

    bool restartGame = false;
    ShowTryAgain(&restartGame);
    
    if (restartGame) {
        printf("Pemain memilih 'Try Again'. Reset game...\n");

        // **Reset semua variabel sebelum InitGame**
        *kalah = false;
        *PermainanBerakhir = false;
        player.lives = MAX_LIVES; // Reset nyawa sebelum InitGame()

        printf("Sebelum InitGame(): kalah = %d, PermainanBerakhir = %d, lives = %d\n", 
               *kalah, *PermainanBerakhir, player.lives);

        InitGame(); // **Reset game**
        
        printf("Setelah InitGame(): kalah = %d, PermainanBerakhir = %d, lives = %d\n", 
               *kalah, *PermainanBerakhir, player.lives);

        return;
    } else {
        printf("Pemain memilih 'Main Menu'. Keluar dari game.\n");
        CloseAudioDevice();
        CloseWindow();
        exit(0);
    }
}

void start() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crossing Highway Grid");
    InitAudioDevice();

    // Muat semua suara dan musik
    LoadAllSounds();

    // Mainkan backsound menu
    PlayMenuBacksound();

    SetTargetFPS(60);

    float volume = 1.0f;
    bool isFullscreen = false;

    while (!WindowShouldClose()) {
        UpdateMusicStream(menuBacksound); // Update musik backsound setiap frame

        MenuOption selectedMenu = ShowMenu();

        if (selectedMenu == MENU_EXIT) {
            StopMenuBacksound();
            UnloadAllSounds();
            CloseAudioDevice();
            CloseWindow();
            return;
        }

        if (selectedMenu == MENU_OPTIONS) {
            ShowOptions(&volume, &isFullscreen);
            continue;
        }

        if (selectedMenu == MENU_START) {
            // Hentikan suara menu saat game dimulai
            StopMenuBacksound();
            InitGame();
            LoadAllTextures();

            Camera2D camera = {0};
            camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
            camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
            camera.rotation = 0.0f;
            camera.zoom = 1.7f;

            while (!WindowShouldClose()) {
                UpdateMusicStream(backgroundMusic1); // Update musik backsound setiap frame

                if (!kalah && !PermainanBerakhir) {
                    camera.target.y -= CAMERA_SPEED;
                    if (player.y * CELL_SIZE > camera.target.y + CAMERA_DEATH_DISTANCE) {
                        kalah = true;
                    }
                }

                if (kalah || PermainanBerakhir) {
                    HandleGameOver(&kalah, &PermainanBerakhir);
                }

                if (IsKeyPressed(KEY_SPACE)) {
                    isPaused = !isPaused;
                }

                if (isPaused) {
                    // Hentikan suara menu saat game di-pause
                    StopMenuBacksound();
                    BeginDrawing();
                    ClearBackground(GRAY);

                    DrawText("PAUSED", SCREEN_WIDTH / 2 - MeasureText("PAUSED", 40) / 2, SCREEN_HEIGHT / 2 - 50, 40, RED);
                    DrawText("Press SPACE to Resume", SCREEN_WIDTH / 2 - MeasureText("Press SPACE to Resume", 20) / 2, SCREEN_HEIGHT / 2, 20, BLACK);
                    DrawText("Press ENTER for Options", SCREEN_WIDTH / 2 - MeasureText("Press ENTER for Options", 20) / 2, SCREEN_HEIGHT / 2 + 30, 20, BLACK);
                    DrawText("Press ESC to Exit to Main Menu", SCREEN_WIDTH / 2 - MeasureText("Press ESC to Exit to Main Menu", 20) / 2, SCREEN_HEIGHT / 2 + 60, 20, BLACK);

                    EndDrawing();

                    if (IsKeyPressed(KEY_ENTER)) {
                        ShowOptions(&volume, &isFullscreen);
                    }
                    if (IsKeyPressed(KEY_ESCAPE)) {
                        break;
                    }

                    continue;
                }

                UpdateGame(&camera);
                DrawGame(camera);
            }

            UnloadAllTextures();
        }
    }

    StopMenuBacksound();
    UnloadAllSounds();
    CloseAudioDevice();
    CloseWindow();
}

void RenderGrid() {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            Color cellColor = DARKGRAY; // Default warna jalan biasa

            if (grid[i][j] == LANE_MARK) {
                cellColor = LANE_COLOR; // Warna garis jalur
            } 
            else if (grid[i][j] == CHECKPOINT_LINE) {
                cellColor = BLUE; // Warna garis checkpoint
            }

            DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, cellColor);
        }
    }
}

void DrawGame(Camera2D camera) {
    BeginDrawing();
    ClearBackground(WHITE);
    BeginMode2D(camera);

    sprintf(coordText, "Coordinate: %2d,%2d", player.x, player.y);
    // Menggambar elemen game dalam dunia (terpengaruh oleh kamera)
    RenderRoads(SCREEN_WIDTH, SCREEN_HEIGHT);

    RenderCars(&numCars, cars);

    RenderFlags();

    RenderHealths();

    RenderPoints();
    
    RenderCharacter(&PlayerSprite, player);
     // Selesai menggambar elemen dalam dunia
    EndMode2D();

    RenderInstructions(player, coordText, level);

    ResetTimer();
    if (PermainanBerakhir) {
        DrawText("MENANG", player.x * CELL_SIZE, player.y * CELL_SIZE, 40, RED);
    }

    if (kalah) {
        DrawText("GAME OVER", player.x * CELL_SIZE, player.y * CELL_SIZE, 40, RED);
        PermainanBerakhir = true;
    }
    
    EndMode2D();
    EndDrawing();
}

void UpdateCarMovement() {
    frameCounter++;
    if (frameCounter >= CAR_MOVE_DELAY) {
        for (int i = 0; i < numCars; i++) {
            int newX = cars[i].x + cars[i].direction * cars[i].speed;
            if (newX < 0) {
                newX = GRID_WIDTH - 1;
            }
            if (newX >= GRID_WIDTH) {
                newX = 0;
            }
            grid[cars[i].y][cars[i].x] = ROAD;
            cars[i].x = newX;
            grid[cars[i].y][cars[i].x] = CAR;

            // Hitung jarak antara mobil dan pemain
            Vector2 playerPos = {player.x * CELL_SIZE, player.y * CELL_SIZE};
            Vector2 carPos = {cars[i].x * CELL_SIZE, cars[i].y * CELL_SIZE};
            float distance = CalculateDistance(playerPos, carPos);

            // Atur volume berdasarkan jarak (semakin dekat, semakin keras)
            float maxDistance = 500.0f; // Jarak maksimum untuk volume penuh
            float volume = 1.0f - (distance / maxDistance);
            if (volume < 0.0f) volume = 0.0f; // Pastikan volume tidak negatif
            SetSoundVolume(carSound, volume);

            // Mainkan suara mobil hanya jika belum diputar
            if (!IsSoundPlaying(carSound)) {
                PlaySound(carSound);
            }
        }
        frameCounter = 0;
    }
}

void InitGrid() {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if ((i == 165 && j == 23) || (i == 39 && j == 53)) {
                grid[i][j] = CHECKPOINT_LINE; // Garis biru setiap 50 baris
            } //else if (i % 8 == 0) {
                //grid[i][j] = LANE_MARK; // Garis putih tiap 8 baris
    
            else if ((i == 131 && j == 51) || (i == 53 && j == 37)) {
                grid[i][j] = HEALTH_UP; // Garis biru setiap 50 baris
            }
            else if ((i == 151 && j == 29) || (i == 21 && j == 55)) {
                grid[i][j] = POINTS;
            }
            else {
                grid[i][j] = ROAD;  //Jalan normal
            }
            //grid [209][j] = LANE_MARK;
            //grid [203][j] = LANE_MARK;
            //grid [199][j] = LANE_MARK;
            //grid [187][j] = LANE_MARK;
        }
    }
}

void checkposition(Player *player) {
    if (grid[player->y][player->x] == CHECKPOINT_LINE) 
    {
        passed = true;
        checkpoint.x = player->x; 
        checkpoint.y = player->y;
        player->score += 10;
        ScorTerakhir = player->y;

        // Tandai checkpoint sudah dilewati agar tidak terus menambah skor
        grid[player->y][player->x] = ROAD;
    }
    else if (grid[player->y][player->x] == HEALTH_UP) 
    {
        ++player->lives;
        
        // Tandai checkpoint sudah dilewati agar tidak terus menambah skor
        grid[player->y][player->x] = ROAD;
    }
    else if (grid[player->y][player->x] == POINTS) 
    {
        player->score += 10;
        
        // Tandai checkpoint sudah dilewati agar tidak terus menambah skor
        grid[player->y][player->x] = ROAD;
    } 
}

void InitGame() {
    printf("MEMULAI INITGAME! Reset semua variabel...\n");

    srand(time(NULL));

    // **Reset semua kondisi permainan**
    kalah = false;
    PermainanBerakhir = false;
    player.score = 0;
    player.lives = MAX_LIVES;
    numCars = NUM_CARS_START;
    carSpeed = CAR_SPEED_START;

    player.x = GRID_WIDTH / 2;
    player.y = GRID_HEIGHT - 2;
    checkpoint.x = player.x;
    checkpoint.y = player.y;

    printf("Game di-reset: lives = %d, score = %d, posisi = (%d, %d)\n",
           player.lives, player.score, player.x, player.y);

    InitGrid();
    printf("Grid berhasil di-reset\n");

    int array[24] = {9, 14, 27, 32, 49, 55, 61, 67, 95, 101, 115, 121, 127, 133, 139, 145, 151, 157, 175, 181, 187, 193, 205, 211};
    int directray[24] = {-1, -1, 1, 1, -1, -1, 1, 1, 1, -1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, 1};

    for (int i = 0; i < numCars; i++) {
        int col = rand() % (GRID_WIDTH - GRID_START);
        int direction = directray[i];

        cars[i] = (Car){col, array[i], carSpeed, direction};
        cars[i].type = (rand() % 4), (rand() % 4), (rand() % 4);
    }

    printf("Mobil berhasil di-reset: jumlah = %d\n", numCars);
}

void ResetCombo() {
    comboMultiplier = 1;
    comboStreak = 0;
}

void CheckCollision() {
    for (int i = 0; i < numCars; i++) {
        if (cars[i].direction == 1)
        {
            if (((player.x <= cars[i].x+7) && (player.x >= cars[i].x-2.3)) && ((player.y <= cars[i].y+2.7) && (player.y >= cars[i].y-2))) {
            player.x = checkpoint.x;
            player.y = checkpoint.y;
            player.lives--;
            if (player.lives <= 0) {
                kalah = true;
            }
            break;
            }
        }
        else
        {
            if (((player.x <= cars[i].x-3) && (player.x >= cars[i].x-9.3)) && ((player.y <= cars[i].y+2.7) && (player.y >= cars[i].y-2))) {
            player.x = checkpoint.x;
            player.y = checkpoint.y;
            player.lives--;
            if (player.lives <= 0) {
                kalah = true;
            }
            break;
            }
        }
    }
}

void UpdateGame(Camera2D *camera) {
    if (!PermainanBerakhir) {
        UpdateCarMovement();

        if (IsKeyPressed(KEY_UP)) {
            movement[0] = true;
            PlaySound(moveCharSound); // Mainkan suara pergerakan karakter
        }
        if (IsKeyPressed(KEY_DOWN)) {
            movement[1] = true;
            PlaySound(moveCharSound); // Mainkan suara pergerakan karakter
        }
        if (IsKeyPressed(KEY_LEFT)) {
            movement[2] = true;
            PlaySound(moveCharSound); // Mainkan suara pergerakan karakter
        }
        if (IsKeyPressed(KEY_RIGHT)) {
            movement[3] = true;
            PlaySound(moveCharSound); // Mainkan suara pergerakan karakter
        }

        if (movement[0]) { player.y -= PLAYER_SPEED + 1; movement[0] = false; }
        if (movement[1]) { player.y += PLAYER_SPEED + 1; movement[1] = false; }
        if (movement[2]) { player.x -= PLAYER_SPEED + 1; movement[2] = false; }
        if (movement[3]) { player.x += PLAYER_SPEED + 1; movement[3] = false; }

        if (player.x < 15) player.x = 15;
        if (player.x >= GRID_WIDTH - 17) player.x = GRID_WIDTH - 17;
        if (player.y < 0) player.y = 0;
        if (player.y >= GRID_HEIGHT) player.y = GRID_HEIGHT - 1;

        checkposition(&player);

        CheckCollision();
    }

    if (player.y == 0) {
        NextLevel(camera, &player);
    }
}

float CalculateDistance(Vector2 pos1, Vector2 pos2) {
    return sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
} 

void StopCarSound() {
    if (IsSoundPlaying(carSound)) {
        StopSound(carSound);
    }
}