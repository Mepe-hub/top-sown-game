#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame; 
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle
    {
        getScreenPos().x,
        getScreenPos().y,
        width * scale,
        height * scale
    };
}
void BaseCharacter::tick(float deltaTime)
{
     //set worldPos to worldPosLastFram
    worldPosLastFrame = worldPos;

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
     if (Vector2Length(velocity) != 0.0f)
    {
        //set worldPos = worlPos + velocity (now plus!)
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        //ternary operator style
        velocity.x < 0.f ? rightLeft = -1.0f : rightLeft = 1.0f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};
    //draw knight
    Rectangle source{frame * width, 0.0f, rightLeft * width, height};
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);

}