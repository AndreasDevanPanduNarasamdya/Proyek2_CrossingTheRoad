#include "raylib.h"
#include "GLOBALHEADER.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "LibraryAndrew.c"
#include "HeaderAndrew.h"
#include "LibraryFaiz.h"
#include "LibraryFaiz.c"

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

    RenderGrid();
    // Menggambar elemen game dalam dunia (terpengaruh oleh kamera)
    
    RenderRoads(SCREEN_WIDTH, SCREEN_HEIGHT);
    RenderCars(&numCars, cars);
    RenderFlags();
    RenderHealths();
    RenderPoints();
    RenderCharacter(&PlayerSprite, player); // Selesai menggambar elemen dalam dunia

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

int main() {
    passed = false;
    DefineArrayCord();
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crossing Highway Grid");
    SetTargetFPS(60);
    InitGame();
    LoadAllTextures();

    camera.target = (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE};
    camera.offset = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.7f;

    while (!WindowShouldClose()) {
        UpdateGame();

        CheckpointLogic();

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