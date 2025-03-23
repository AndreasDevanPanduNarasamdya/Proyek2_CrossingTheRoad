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
    if (level == 1)
    {
        DrawTextureEx(background, (Vector2){150,0}, 0.0f, 0.25, WHITE);
    }
    else if (level == 2)
    {
        DrawTextureEx(lvl2background, (Vector2){150,0}, 0.0f, 0.25, WHITE);
    }
    else if (level == 3)
    {
        DrawTextureEx(lvl3background, (Vector2){150,0}, 0.0f, 0.25, WHITE);
    }
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

    //DrawTextureEx(*PlayerSprite, (Vector2){player.x * CELL_SIZE, (player.y * CELL_SIZE)+2}, 0.0f, 0.1f, WHITE);
    //DrawTextureEx(*PlayerSprite, (Vector2){player.x * CELL_SIZE, (player.y * CELL_SIZE)+1}, 0.0f, 0.1f, WHITE);
    //DrawTextureEx(*PlayerSprite, (Vector2){player.x * CELL_SIZE, (player.y * CELL_SIZE)}, 0.0f, 0.1f, WHITE);
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
        currentFrame = (currentFrame + 1) % 4; 
    }

    DrawTextureEx(FlagAsset[currentFrame], (Vector2){500, 375}, 0.0f, 0.1, WHITE);
    DrawTextureEx(FlagAsset[currentFrame], (Vector2){200, 1650}, 0.0f, 0.1, WHITE);
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

    DrawTextureEx(HealthAsset[currentFrame], (Vector2){345, 548}, 0.0f, 0.07, WHITE);
    DrawTextureEx(HealthAsset[currentFrame], (Vector2){478, 1323}, 0.0f, 0.07, WHITE);
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

    DrawTextureEx(PointAsset[currentFrame], (Vector2){178, 548}, 0.0f, 0.07, WHITE);
    DrawTextureEx(PointAsset[currentFrame], (Vector2){356, 1530}, 0.0f, 0.07, WHITE);
}

 void RenderCars(int *numCars, Car cars[])
{
    for (int i = 0; i < *numCars; i++)  // Use *numCars instead of numCars
    {
        int x = cars[i].x * CELL_SIZE;
        int y = cars[i].y * CELL_SIZE;
        Texture2D carTexture;

        if ((y != 95 * CELL_SIZE && y != 101 * CELL_SIZE) && (y != 78 * CELL_SIZE)) 
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
        else if (y != 95 * CELL_SIZE && y != 101 * CELL_SIZE)
        {
            carTexture = Train;
        }
        else if (y != 78 * CELL_SIZE)
        {
            carTexture = logs;
        }
        if (cars[i].direction == 1)
        {
            if ((y != 95 * CELL_SIZE && y != 101 * CELL_SIZE) && (y != 78 * CELL_SIZE))
            {
                DrawTextureEx(carTexture, (Vector2){x,y}, 0.0f, 0.03f, WHITE);
            }
            else if (y != 78 * CELL_SIZE)
            {
                DrawTextureEx(carTexture, (Vector2){x,y}, 0.0f, 0.1f, WHITE);
            }
            else
            {
                DrawTextureEx(carTexture, (Vector2){x,y}, 0.0f, 0.17f, WHITE);
                DrawTextureEx(carTexture, (Vector2){x+5,y}, 0.0f, 0.17f, WHITE);
                DrawTextureEx(carTexture, (Vector2){x+10,y}, 0.0f, 0.17f, WHITE);
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
    UnloadTexture(checkpointtxt);
    UnloadTexture(healthup);
}

void LoadAllTextures()
{
    char filename[34];
    TaxiTexture = LoadTexture("Assets/sprite/taxi.png");
    TruckTexture = LoadTexture("Assets/sprite/gruppesechs_van.png");
    VanTexture = LoadTexture("Assets/sprite/vanbankk.png");
    Mustang = LoadTexture("Assets/sprite/mustang.png");
    Character.PlayerFrontSprite = LoadTexture("Assets/sprite/chickenlittlefront.png");
    Character.PlayerBackSprite = LoadTexture("Assets/sprite/chickenlittleback.png");
    Character.PlayerSideLeftSprite = LoadTexture("Assets/sprite/chickenlittlesideleft.png");
    Character.PlayerSideRightSprite = LoadTexture("Assets/sprite/chickenlittlesideright.png");
    background = LoadTexture("Assets/sprite/mapproyek2.png");
    logs = LoadTexture("Assets/sprite/logbridge.png");
    Train = LoadTexture("Assets/sprite/KAI.png");
    checkpointflag = LoadTexture("Assets/sprite/checkpointflag.png");
    checkpointtxt = LoadTexture("Assets/sprite/checkpointtxt.png");
    healthup = LoadTexture("Assets/sprite/healthpowerup.png");
    points = LoadTexture("Assets/sprite/pointsup.png");
    lvl3background = LoadTexture("Assets/sprite/map2proyek3.png");
    for (int i = 0; i<4; i++)
    {
        sprintf(filename, "Assets/sprite/FlagAnim/checkpointflagassprite%i.png", i+1);
        FlagAsset[i] = LoadTexture(filename);
    }
    for (int i = 0; i<6; i++)
    {
        sprintf(filename, "Assets/sprite/PointsAnim/pointsup%i.png", i+1);
        PointAsset[i] = LoadTexture(filename);
    }
    for (int i = 0; i<6; i++)
    {
        sprintf(filename, "Assets/sprite/HealthAnim/health%i.png", i+1);
        HealthAsset[i] = LoadTexture(filename);
    }
}

void RenderInstructions(Player player, char *coordText, int level)
{

    // Menampilkan teks di sudut kiri atas layar
    DrawText(TextFormat("Score: %d", player.score), margin, margin, 20, WHITE);
    DrawText(TextFormat("Lives: %d", player.lives), margin, margin + 30, 20, WHITE);
    DrawText(TextFormat("Level: %d", level), margin, margin + 60, 20, WHITE);
    DrawText(coordText, margin, margin + 90, 20, WHITE);
    DrawText("Use Arrow Keys to Move", margin, margin + 120, 20, WHITE);
    DrawText(TextFormat("point: %d", point), margin, margin + 150, 20, WHITE);
}

