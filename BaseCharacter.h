#pragma once
//otherwise the class will be used twice in main.cpp because of Enemy and Character!
#include "raylib.h"

class BaseCharacter
{
    public:
        BaseCharacter();
        
        Vector2 getWorldPos() { return worldPos; } 
        void undoMovement();
        Rectangle getCollisionRec();
    protected:
        Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
        Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
        Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");
        Vector2 screenPos{};
        Vector2 worldPos{};
        Vector2 worldPosLastFrame{};
        float rightLeft{1.0f};
        //animation variables
        float runningTime{};
        int frame{};
        int maxFrames{6};
        float updateTime{1.0f / 12.0f};
        float speed = 4.0f;
        float width{};
        float height{};
        float scale{4.0f};
};