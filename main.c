#include "raylib.h"
#include "GLOBALHEADER.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "LibraryAndrew.c"
#include "HeaderAndrew.h"
#include "LibraryFaiz.h"
#include "LibraryFaiz.c"
#include "LibraryAzzam.h"
#include "LibraryAzzam.c"
#include "menu.h"
#include "menu.c"


void DrawGame(Camera2D camera) {
    
    BeginDrawing();
    ClearBackground(WHITE);

    BeginMode2D(camera);

    sprintf(coordText, "X: %d, Y: %d", player.x, player.y);

    RenderGrid();
    // Menggambar elemen game dalam dunia (terpengaruh oleh kamera)
    
    RenderRoads(SCREEN_WIDTH, SCREEN_HEIGHT);

    RenderCars(&numCars, cars);

    RenderCharacter(&PlayerSprite, player);

    EndMode2D(); // Selesai menggambar elemen dalam dunia

    // Menggambar elemen UI/HUD (agar tetap di layar)
    RenderInstructions(player, coordText, level);

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

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crossing Highway Grid");
    SetTargetFPS(60);

    MenuOption selectedMenu = ShowMenu();
    if (selectedMenu == MENU_EXIT) {
        CloseWindow();
        return 0;
    }
    
    InitGame();
    LoadAllTextures();

    camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
    camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    while (!WindowShouldClose()) {
        UpdateGame();

        if (!kalah && !PermainanBerakhir) {
            camera.target.y -= CAMERA_SPEED ; // Kamera selalu bergerak ke depan

            // Cek jika pemain tertinggal terlalu jauh
            if (player.y * CELL_SIZE > camera.target.y + CAMERA_DEATH_DISTANCE) {
                kalah = true;
            }
        }

        DrawGame(camera);
    }

    UnloadAllTextures();
    CloseWindow();
    return 0;
}