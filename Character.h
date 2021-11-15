#pragma once
#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int winWidth, int winHeight); 
    virtual void tick(float deltaTime) override;
    virtual Vector2 getScreenPos()override;

private:
int windowWidth{};
int windowHeight{};
float rotation;
Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
Rectangle weaponCollisionRec{};

};