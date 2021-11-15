#include "Character.h"
#include "raymath.h"

Character::Character(int winWidth, int winHeight) :
    windowWidth(winWidth),
    windowHeight(winHeight)
{
    width = texture.width/maxFrames;
    height = texture.height;
   
}

//setting screenPos with a getter function
Vector2 Character::getScreenPos()
{
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width),
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)
    };
}

void Character::tick(float deltaTime)
{
    if(!getAlive()) return;

    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0f;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0f;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0f;

   BaseCharacter::tick(deltaTime);

    //sword position
    Vector2 origin;
    Vector2 offSet;

    if(rightLeft > 0.0f)
    {
        origin = {0.0f, weapon.height * scale};
        offSet = {35.0f, 55.0f};
        weaponCollisionRec = {
            getScreenPos().x + offSet.x,
            getScreenPos().y + offSet.y - weapon.height *scale,
            weapon.width * scale,
            weapon.height * scale 
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.0f : rotation = 0.0f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offSet = {25.0f, 50.0f};
        weaponCollisionRec = {
            getScreenPos().x + offSet.x - weapon.width * scale,
            getScreenPos().y + offSet.y - weapon.height *scale,
            weapon.width * scale,
            weapon.height * scale 
        };
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -35.0f : rotation = 0.0f;
    }

    //draw the sword with TexturePro
    Rectangle source{0.0f, 0.0f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest{getScreenPos().x + offSet.x, getScreenPos().y + offSet.y , weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    //DrawRectangleLines(weaponCollisionRec.x, weaponCollisionRec.y, weaponCollisionRec.width, weaponCollisionRec.height, RED);
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if(health <= 0.0f)
    {
        setAlive(false);
    }
}

