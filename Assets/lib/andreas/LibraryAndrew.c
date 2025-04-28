#include "../header.h"

int margin = 20;

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
    static float lastFrameTime = 0.0f;
    float timePerFrame = 0.1f;  // 0.1s between each frame
    static int drawStep = 0;
    static Vector2 LastMovement = (Vector2){0, 0};

    if (player.x > LastMovement.x)
    {
        Character.countdown = 6;
        *PlayerSprite = Character.PlayerSideRightSprite;
    }
    else if (player.x < LastMovement.x)
    {
        Character.countdown = 6;
        *PlayerSprite = Character.PlayerSideLeftSprite;
    }
    else if (player.y > LastMovement.y)
    {
        Character.countdown = 6;
        *PlayerSprite = Character.PlayerFrontSprite;
    }
    else if (player.y < LastMovement.y)
    {
        Character.countdown = 6;
        *PlayerSprite = Character.PlayerBackSprite;
    }

    LastMovement = (Vector2){player.x, player.y};

    if (GetTime() - lastFrameTime >= timePerFrame)
    {
        lastFrameTime = GetTime();
        if (Character.countdown > 0)
        {
            drawStep = (drawStep + 1) % 3;
        }
        else
        {
            drawStep = 0;
        }
        
    }

    switch (drawStep)
    {
        case 0:
            DrawTextureEx(*PlayerSprite, (Vector2){player.x * CELL_SIZE, (player.y+2) * CELL_SIZE}, 0.0f, 0.1f, WHITE);
            Character.countdown--;
            break;
        case 1:
            DrawTextureEx(*PlayerSprite, (Vector2){player.x * CELL_SIZE, (player.y+1) * CELL_SIZE}, 0.0f, 0.1f, WHITE);
            Character.countdown--;
            break;
        case 2:
            DrawTextureEx(*PlayerSprite, (Vector2){player.x * CELL_SIZE, player.y * CELL_SIZE}, 0.0f, 0.1f, WHITE);
            Character.countdown--;
            break;
    }
}


void Renderchkpointtxt() 
{
        DrawTextureEx(checkpointtxt, (Vector2){margin + 240, margin}, 0, 0.2, WHITE);
}

// Call this function **every frame** in the game loop
void CheckpointLogic() {
    if (player.score > lastscore) {
        lastscore = player.score;  // Update last score
        showCheckpointText = true;
        checkpointTimer = 300;  // Show for 300 frames (~5 seconds at 60 FPS)
    }
}

void RenderFlags()
{
    static int currentFrame = 0;
    float timePerFrame = 0.1f; 
    static float lastFrameTime = 0.0f;

    if (GetTime() - lastFrameTime >= timePerFrame) {
        lastFrameTime = GetTime();
        currentFrame = (currentFrame) % 4;
    }

    DrawTextureEx(FlagAsset[currentFrame], (Vector2){50*CELL_SIZE, 37*CELL_SIZE}, 0.0f, 0.1, BLANK);
    DrawTextureEx(FlagAsset[currentFrame], (Vector2){20*CELL_SIZE, 165*CELL_SIZE}, 0.0f, 0.1, BLANK);
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
    static int currentFrame = 0;
    float timePerFrame = 0.1f; 
    static float lastFrameTime = 0.0f;
    
    if (GetTime() - lastFrameTime >= timePerFrame) {
        lastFrameTime = GetTime();
        currentFrame = (currentFrame + 1) % 6; 
    }

    if (level == 1)
    {
        Vector2 health1 = {345, 548};
        Vector2 health2 = {478, 1323};
        DrawTextureEx(HealthAsset[currentFrame], (Vector2)health1, 0.0f, 0.07, WHITE);
        DrawTextureEx(HealthAsset[currentFrame], (Vector2)health2, 0.0f, 0.07, WHITE);
        if ((player.x >= ((Vector2)health1).x-10 && player.x <= ((Vector2)health1).x+10) && (player.y >= ((Vector2)health1).y-10 && player.y <= ((Vector2)health1).y+10))
        {
            ++player.lives;
            health1 = (Vector2){0,0};
        }
        if ((player.x >= ((Vector2)health2).x-10 && player.x <= ((Vector2)health2).x+10) && (player.y >= ((Vector2)health2).y-10 && player.y <= ((Vector2)health2).y+10))
        {
            ++player.lives;
            health2 = (Vector2){0,0};
        }
    }
    else if (level == 2)
    {
        Vector2 health1 = {256, 305};
        Vector2 health2 = {254, 879};
        DrawTextureEx(HealthAsset[currentFrame], (Vector2)health1, 0.0f, 0.07, WHITE);
        DrawTextureEx(HealthAsset[currentFrame], (Vector2)health2, 0.0f, 0.07, WHITE);
    }
    else if (level == 3)
    {
        Vector2 health1 = {167, 365};
        Vector2 health2 = {567, 683};
        Vector2 health3 = {326, 1500};
        DrawTextureEx(HealthAsset[currentFrame], (Vector2)health1, 0.0f, 0.07, WHITE);
        DrawTextureEx(HealthAsset[currentFrame], (Vector2)health2, 0.0f, 0.07, WHITE);
        DrawTextureEx(HealthAsset[currentFrame], (Vector2)health3, 0.0f, 0.07, WHITE);
    }


}

void RenderPoints()
{
    static int currentFrame = 0;
    float timePerFrame = 0.1f;
    static float lastFrameTime = 0.0f;

    if (GetTime() - lastFrameTime >= timePerFrame) {
        lastFrameTime = GetTime();
        currentFrame = (currentFrame + 1) % 6; 
    }

    if (level == 1)
    {
        DrawTextureEx(PointAsset[currentFrame], (Vector2){18*CELL_SIZE, 55*CELL_SIZE}, 0.0f, 0.07, WHITE);
        DrawTextureEx(PointAsset[currentFrame], (Vector2){35*CELL_SIZE, 153*CELL_SIZE}, 0.0f, 0.07, WHITE);
    }
    else if (level == 2)
    {
        DrawTextureEx(PointAsset[currentFrame], (Vector2){26*CELL_SIZE, 34*CELL_SIZE}, 0.0f, 0.07, WHITE);
        DrawTextureEx(PointAsset[currentFrame], (Vector2){45*CELL_SIZE, 69*CELL_SIZE}, 0.0f, 0.07, WHITE);
        DrawTextureEx(PointAsset[currentFrame], (Vector2){35*CELL_SIZE, 153*CELL_SIZE}, 0.0f, 0.07, WHITE);
    }
    else if (level == 3)
    {
        DrawTextureEx(PointAsset[currentFrame], (Vector2){67*CELL_SIZE, 38*CELL_SIZE}, 0.0f, 0.07, WHITE);
        DrawTextureEx(PointAsset[currentFrame], (Vector2){32*CELL_SIZE, 53*CELL_SIZE}, 0.0f, 0.07, WHITE);
        DrawTextureEx(PointAsset[currentFrame], (Vector2){57*CELL_SIZE, 79*CELL_SIZE}, 0.0f, 0.07, WHITE);
        DrawTextureEx(PointAsset[currentFrame], (Vector2){45*CELL_SIZE, 134*CELL_SIZE}, 0.0f, 0.07, WHITE);
    }



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
    Character.PlayerFrontSprite = LoadTexture("Assets/sprite/chickenlittlefront.png");
    Character.PlayerBackSprite = LoadTexture("Assets/sprite/chickenlittleback.png");
    Character.PlayerSideLeftSprite = LoadTexture("Assets/sprite/chickenlittlesideleft.png");
    Character.PlayerSideRightSprite = LoadTexture("Assets/sprite/chickenlittlesideright.png");
    background = LoadTexture("Assets/sprite/mapproyek2.png");
    lvl1background = LoadTexture("Assets/sprite/mapproyek2.png");
    lvl2background = LoadTexture("Assets/sprite/map2proyek2.png");
    lvl3background = LoadTexture("Assets/sprite/map2proyek3.png");
    logs = LoadTexture("Assets/sprite/logbridge.png");
    checkpointtxt = LoadTexture("Assets/sprite/checkpointtxt.png");
    healthup = LoadTexture("Assets/sprite/healthpowerup.png");
    points = LoadTexture("Assets/sprite/pointsup.png");
    FlagAsset[0] = LoadTexture("Assets/sprite/FlagAnim/checkpointflagassprite1.png");
    FlagAsset[1] = LoadTexture("Assets/sprite/FlagAnim/checkpointflagassprite2.png");
    FlagAsset[2] = LoadTexture("Assets/sprite/FlagAnim/checkpointflagassprite3.png");
    FlagAsset[3] = LoadTexture("Assets/sprite/FlagAnim/checkpointflagassprite4.png");
    PointAsset[0] = LoadTexture("Assets/sprite/PointsAnim/pointsup1.png");
    PointAsset[1] = LoadTexture("Assets/sprite/PointsAnim/pointsup2.png");
    PointAsset[2] = LoadTexture("Assets/sprite/PointsAnim/pointsup3.png");
    PointAsset[3] = LoadTexture("Assets/sprite/PointsAnim/pointsup4.png");
    PointAsset[4] = LoadTexture("Assets/sprite/PointsAnim/pointsup5.png");
    PointAsset[5] = LoadTexture("Assets/sprite/PointsAnim/pointsup6.png");
    HealthAsset[0] = LoadTexture("Assets/sprite/HealthAnim/health1.png");
    HealthAsset[1] = LoadTexture("Assets/sprite/HealthAnim/health2.png");
    HealthAsset[2] = LoadTexture("Assets/sprite/HealthAnim/health3.png");
    HealthAsset[3] = LoadTexture("Assets/sprite/HealthAnim/health4.png");
    HealthAsset[4] = LoadTexture("Assets/sprite/HealthAnim/health5.png");
    HealthAsset[5] = LoadTexture("Assets/sprite/HealthAnim/health6.png");


}

void RenderInstructions(Player player, char *coordText, int level, char *NewCoordinate)
{

    // Menampilkan teks di sudut kiri atas layar
    DrawText(TextFormat("Score: %d", player.score), margin, margin, 20, WHITE);
    DrawText(TextFormat("Lives: %d", player.lives), margin, margin + 30, 20, WHITE);
    DrawText(TextFormat("Level: %d", level), margin, margin + 60, 20, WHITE);
    DrawText(coordText, margin, margin + 90, 20, WHITE);
    DrawText("Use Arrow Keys to Move", margin, margin + 120, 20, WHITE);
    DrawText(TextFormat("health: %d", health_upgrade), margin, margin + 150, 20, WHITE);
    DrawText(NewCoordinate, margin, margin + 180, 20, WHITE);
}

