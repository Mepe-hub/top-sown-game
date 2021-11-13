#include "Enemy.h"

//intitializer list does not work with derived classes! so no colon behind run_texture and then worldPos(pos)
Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
   
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width/maxFrames;
    height = texture.height;

}

void Enemy::tick(float deltaTime)
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
    //draw knight
    Rectangle source{frame * width, 0.0f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);
}
