#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 getWorldPos() { return worldPos; }
    void setScreenPos(int winWidth, int winHeight);
    void tick(float deltaTime);

private:
    Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");
    Vector2 screenPos{};
    Vector2 worldPos{};
    float rightLeft{1.0f};
    //animation variables
    float runningTime{};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.0f / 12.0f};
    const float speed = 4.0f;
};
//actual function body outside of class for overview
void Character::setScreenPos(int winWidth, int winHeight)
{
        screenPos = 
        {
        (float)winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f),
        (float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)
        };
}

void Character::tick(float deltaTime)
{
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0f;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0f;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0f;

    if (Vector2Length(direction) != 0.0f)
    {
        //set worldPos = worlPos + direction (now plus!)
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        //ternary operator style
        direction.x < 0.f ? rightLeft = -1.0f : rightLeft = 1.0f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    //update animation
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        runningTime = 0.0f;
        //update animation frame
        frame++;
        if (frame > maxFrames)
            frame = 0;
    }
    //draw knight
    Rectangle source{frame * (float)texture.width / 6.0f, 0.0f, rightLeft * (float)texture.width / 6.0f, (float)texture.height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * (float)texture.width / 6.0f, 4.0f * (float)texture.height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
    //UnloadTexture(texture);
}

int main()
{
    const int windowWidth = 384;
    const int windowHeight = 384;

    InitWindow(windowWidth, windowHeight, "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/worldmap.png");
    Vector2 mapPos{};

    //instance of knight
    Character knight;
    knight.setScreenPos(windowWidth, windowHeight);
    

    //Game loop
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.0f);

        //draw map
        DrawTextureEx(map, mapPos, 0.0f, 4.0f, WHITE);

        //update knight
        knight.tick(GetFrameTime());

        EndDrawing();
    }

    UnloadTexture(map);
    
}
