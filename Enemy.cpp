#include "Enemy.h"
#include "raymath.h"

//intitializer list does not work with derived classes! so no colon behind run_texture and then worldPos(pos)
Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
   
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width/maxFrames;
    height = texture.height;
    speed = 3.0f;

}


void Enemy::tick(float deltaTime)
{

    /*this was the code used before velocity to give enemy AI
    //get toTarget vector
    Vector2 toTarget {Vector2Subtract(target->getScreenPos(), screenPos)};
    //normalize the vector
    toTarget = Vector2Normalize(toTarget);
    //multiply vector by a speed variable
    toTarget = Vector2Scale(toTarget, speed);
    */

    if(!getAlive()) return;

    //velocity = {Vector2Subtract(target->getScreenPos(), getScreenPos())};
    if(Vector2Length(velocity) < radius) velocity = {};

    BaseCharacter::tick(deltaTime);

    //damge to character
    if(CheckCollisionRecs(target->getCollisionRec(), getCollisionRec()))
    {
        target->takeDamage(damagePerSec * deltaTime);
    }
   
}

Vector2 Enemy::getScreenPos()
{
    return Vector2Subtract(worldPos, target->getWorldPos());
}
