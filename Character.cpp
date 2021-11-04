#include "Character.h"
#include "raymath.h"

Character::Character()
{
    width = texture.width/maxFrames;
    height = texture.height;
}

void Character::setScreenPos(int winWidth, int winHeight)
{
        screenPos = 
        {
        (float)winWidth / 2.0f - 4.0f * (0.5f * width),
        (float)winHeight / 2.0f - 4.0f * (0.5f * height)
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
    Rectangle source{frame * width, 0.0f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, 4.0f * width, 4.0f * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);

}