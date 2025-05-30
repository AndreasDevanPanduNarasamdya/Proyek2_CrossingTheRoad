#include "../header.h"

int margin = 20;

void RenderRoads()
{
    if (level == 1)
    {
        DrawTextureEx(newmap, (Vector2){250, -370}, 0.0f, 0.25f, WHITE);
    }
    // else if (level == 2)
    // {
    //     DrawTextureEx(newmap2, (Vector2){250, -306}, 0.0f, 0.315f, WHITE);
    //     DrawTextureEx(newmap, (Vector2){130, -370}, 0.0f, 0.25f, WHITE);
    // }
    else if (level == 2)
    {
        DrawTextureEx(newmap2, (Vector2){200, -306}, 0.0f, 0.315f, WHITE);
    }
}

void Renderchkpointtxt()
{
    DrawTextureEx(checkpointtxt, (Vector2){margin + 240, margin}, 0, 0.2, WHITE);
}

// Call this function **every frame** in the game loop
void CheckpointLogic()
{
    if (player.score > lastscore)
    {
        lastscore = player.score; // Update last score
        showCheckpointText = true;
        checkpointTimer = 300; // Show for 300 frames (~5 seconds at 60 FPS)
    }
}

// void HealthLogic(HealthHP *Health)
// {
//     if (player.lives > lastlives)
//     {
//         HealthHP TempHealth = *Health;
//         while (TempHealth != NULL && TempHealth->healthgrid)
//     }
// }

void RenderFlags(Checkpoint *First)
{
    Checkpoint TempFlag = *First;
    static int currentFrame = 0;
    float timePerFrame = 0.1f; 
    static float lastFrameTime = 0.0f;

    if (GetTime() - lastFrameTime >= timePerFrame) {
    lastFrameTime = GetTime();
    currentFrame = (currentFrame + 1) % 4;
    }

    while (TempFlag != NULL)
    {
    DrawTextureEx(FlagAsset[currentFrame], (Vector2){TempFlag->x, TempFlag->y}, 0.0f, 0.1, WHITE);
    TempFlag = TempFlag->Next;
    }

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


void RenderHealths(HealthHP *Health)
{
    HealthHP TempHealth = *Health;
    static int currentFrame = 0;
    float timePerFrame = 0.1f; 
    static float lastFrameTime = 0.0f;

    if (GetTime() - lastFrameTime >= timePerFrame) {
        lastFrameTime = GetTime();
        currentFrame = (currentFrame + 1) % 6; 
    }

    HealthHP drawPtr = *Health;
    while (drawPtr != NULL)
    {
        if (drawPtr->enabled == true)
        {
            DrawTextureEx(HealthAsset[currentFrame],
                (Vector2){drawPtr->x, drawPtr->y},
                0.0f, 0.1f, WHITE);
        }

        drawPtr = drawPtr->Next;
    }
    //DrawTextureEx(healthup, (Vector2){345, 548}, 0.0f, 0.07, WHITE);
    //DrawTextureEx(healthup, (Vector2){478, 1323}, 0.0f, 0.07, WHITE);
}

void RenderPoints(PointsXP *Points)
{
    PointsXP TempPoints = *Points;
    static int currentFrame = 0;
    float timePerFrame = 0.1f;
    static float lastFrameTime = 0.0f;

    if (GetTime() - lastFrameTime >= timePerFrame) {
        lastFrameTime = GetTime();
        currentFrame = (currentFrame + 1) % 6; 
    }

    PointsXP draw = *Points;
    while (draw != NULL)
    {
        if (draw->enabled == true)
        {
            DrawTextureEx(PointAsset[currentFrame], (Vector2){draw->x, draw->y}, 0.0f, 0.07, WHITE);
        }
        draw = draw->Next;
    }
}

void RenderEggs(EggyPoints *Egg)
{
    static int currentFrame = 0;
    float timePerFrame = 0.1f; 
    static float lastFrameTime = 0.0f;

    if (GetTime() - lastFrameTime >= timePerFrame) {
        lastFrameTime = GetTime();
        currentFrame = (currentFrame + 1) % 6; 
    }

    EggyPoints EggTemp = *Egg;
    while (EggTemp != NULL)
    {
        if (EggTemp->enabled == true)
        {
            DrawTextureEx(EggyAsset[currentFrame],
                (Vector2){EggTemp->x, EggTemp->y},
                0.0f, 0.1f, WHITE);
        }

        EggTemp = EggTemp->Next;
    }
}

void RenderCars(Carlist *carList)
{
    address curr = carList->First;
    while (curr != NULL)
    {
        Car car = curr->info;
        int x = car.x * CELL_SIZE;
        int y = car.y * CELL_SIZE;
        Texture2D carTexture;

        if (y != 95 * CELL_SIZE && y != 101 * CELL_SIZE && y != 77 * CELL_SIZE)
        {
            if (car.type == 0)
                carTexture = TaxiTexture;
            else if (car.type == 1)
                carTexture = TruckTexture;
            else if (car.type == 2)
                carTexture = VanTexture;
            else if (car.type == 3)
                carTexture = Mustang;
        }
        else if (y == 77 * CELL_SIZE)
        {
            carTexture = train;
        }
        else
        {
            carTexture = logs;
        }

        if (car.direction == 1)
        {
            if (y != 95 * CELL_SIZE && y != 101 * CELL_SIZE)
                DrawTextureEx(carTexture, (Vector2){x, y}, 0.0f, 0.03f, WHITE);
            else
                DrawTextureEx(carTexture, (Vector2){x, y}, 0.0f, 0.1f, WHITE);
        }
        else
        {
            if (y != 95 * CELL_SIZE && y != 101 * CELL_SIZE)
                DrawTextureEx(carTexture, (Vector2){x, y + 40}, 180.0f, 0.03f, WHITE);
            else
                DrawTextureEx(carTexture, (Vector2){x, y + 40}, 180.0f, 0.1f, WHITE);
        }

        curr = curr->next;
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
    PlayerSprite = LoadTexture("Assets/sprite/chickenlittlesideright.png");
    newmap = LoadTexture("Assets/sprite/newmaplitelvl2png.png");
    background = LoadTexture("Assets/sprite/mapproyek2.png");
    // newmap2 = LoadTexture("Assets/sprite/newmaplvl2.png");
    // newmap2 = LoadTexture("Assets/sprite/newmaplitelvl2.png");
    // newmap2 = LoadTexture("Assets/sprite/newmaplitelvl2.png");
    newmap2 = LoadTexture("Assets/sprite/newmaplitelvl2.png");
    logs = LoadTexture("Assets/sprite/logbridge.png");
    train = LoadTexture("Assets/sprite/KAIout.png");
    checkpointflag = LoadTexture("Assets/sprite/checkpointflag.png");
    checkpointtxt = LoadTexture("Assets/sprite/checkpointtxt.png");
    healthup = LoadTexture("Assets/sprite/healthpowerup.png");
    points = LoadTexture("Assets/sprite/pointsup.png");
    Character.PlayerFrontSprite = LoadTexture("Assets/sprite/chickenlittlefront.png");
    Character.PlayerBackSprite = LoadTexture("Assets/sprite/chickenlittleback.png");
    Character.PlayerSideLeftSprite = LoadTexture("Assets/sprite/chickenlittlesideleft.png");
    Character.PlayerSideRightSprite = LoadTexture("Assets/sprite/chickenlittlesideright.png");
    FlagAsset[0] = LoadTexture("Assets/sprite/FlagAnim/checkpointflagassprite1.png");
    FlagAsset[1] = LoadTexture("Assets/sprite/FlagAnim/checkpointflagassprite2.png");
    FlagAsset[2] = LoadTexture("Assets/sprite/FlagAnim/checkpointflagassprite3.png");
    FlagAsset[3] = LoadTexture("Assets/sprite/FlagAnim/checkpointflagassprite4.png");
    HealthAsset[0] = LoadTexture("Assets/sprite/HealthAnim/health1.png");
    HealthAsset[1] = LoadTexture("Assets/sprite/HealthAnim/health2.png");
    HealthAsset[2] = LoadTexture("Assets/sprite/HealthAnim/health3.png");
    HealthAsset[3] = LoadTexture("Assets/sprite/HealthAnim/health4.png");
    HealthAsset[4] = LoadTexture("Assets/sprite/HealthAnim/health5.png");
    HealthAsset[5] = LoadTexture("Assets/sprite/HealthAnim/health6.png");
    PointAsset[0] = LoadTexture("Assets/sprite/PointsAnim/pointsup1.png");
    PointAsset[1] = LoadTexture("Assets/sprite/PointsAnim/pointsup2.png");
    PointAsset[2] = LoadTexture("Assets/sprite/PointsAnim/pointsup3.png");
    PointAsset[3] = LoadTexture("Assets/sprite/PointsAnim/pointsup4.png");
    PointAsset[4] = LoadTexture("Assets/sprite/PointsAnim/pointsup5.png");
    PointAsset[5] = LoadTexture("Assets/sprite/PointsAnim/pointsup6.png");
    EggyAsset[0] = LoadTexture("Assets/sprite/eggy/eggy1.png");
    EggyAsset[1] = LoadTexture("Assets/sprite/eggy/eggy2.png");
    EggyAsset[2] = LoadTexture("Assets/sprite/eggy/eggy3.png");
    EggyAsset[3] = LoadTexture("Assets/sprite/eggy/eggy4.png");
    EggyAsset[4] = LoadTexture("Assets/sprite/eggy/eggy5.png");
    EggyAsset[5] = LoadTexture("Assets/sprite/eggy/eggy6.png");
}

void RenderInstructions(Player player, char *coordText, int level)
{
    // Menampilkan teks di sudut kiri atas layar
    DrawText(TextFormat("Score: %d", player.score), margin, margin, 20, WHITE);
    DrawText(TextFormat("Lives: %d", player.lives), margin, margin + 30, 20, WHITE);
    DrawText(TextFormat("Level: %d", level), margin, margin + 60, 20, WHITE);
    DrawText(coordText, margin, margin + 90, 20, WHITE);
    DrawText(TextFormat("health: %d", health_upgrade), margin, margin + 150, 20, WHITE);
}
