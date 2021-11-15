#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    const int windowWidth = 384;
    const int windowHeight = 384;

    InitWindow(windowWidth, windowHeight, "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/RPG Nature Tileset.png");
    Vector2 mapPos{};
    const float mapScale{4.0f};

    //instance of knight with braced initialization!
    Character knight{windowWidth, windowHeight};

    //instance of enemy
    Enemy goblin    {
                    Vector2{800.0f, 300.0f}, 
                    LoadTexture("characters/goblin_idle_spritesheet.png"), 
                    LoadTexture("characters/goblin_run_spritesheet.png")
                    };

    Enemy slime     {
                    Vector2{500.0f, 700.0f}, 
                    LoadTexture("characters/slime_idle_spritesheet.png"), 
                    LoadTexture("characters/slime_run_spritesheet.png")
                    };

    //array of enemies
    Enemy* enemies[] {&goblin, &slime}; 

    for(auto enemy : enemies)
    {
        enemy->setTarget(&knight); // -> because of derefenrencing with function!!!
    }

    //instance of prop
    Prop props[2]{
        Prop {Vector2{600.0f, 300.0f}, LoadTexture("nature_tileset/Rock.png")},
        Prop {Vector2{400.0f, 700.0f}, LoadTexture("nature_tileset/Log.png")}
    };
    //Game loop
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.0f);

        //draw map
        DrawTextureEx(map, mapPos, 0.0f, mapScale, WHITE);
        
        //draw props
        for(int i = 0; i < 2; i++) //or: for(auto prop: props)
        {
            props[i].Render(knight.getWorldPos());
        }
        
        //draw damage to screen
        if(!knight.getAlive())
        {
            DrawText("Game Over", 55.0f, 45.0f, 40, RED);
            EndDrawing();
            continue;
        }
        else
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.0f, 45.0f, 40, RED );

        }

        //update knight
        knight.tick(GetFrameTime());
        
        //update enemies
        for(auto enemy : enemies)
        {
             enemy->tick(GetFrameTime());
        }
       
        
        //check map bounds
        if(knight.getWorldPos().x < 0.0f 
            || knight.getWorldPos().y < 0.0f 
            || knight.getWorldPos().x + windowWidth > map.width * mapScale
            || knight.getWorldPos().y + windowHeight > map.height * mapScale
        )
        {
            knight.undoMovement();
        }
        
        for(auto prop : props)
        {
            if(CheckCollisionRecs(knight.getCollisionRec(), prop.getCollisionRec(knight.getWorldPos())))
            {
                knight.undoMovement();
            };
           
        }
        
        for(auto enemy : enemies)
        {
             if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    if(CheckCollisionRecs(enemy->getCollisionRec(), knight.getCollisionRec()))
                        enemy->setAlive(false);
                }
        }
       
        

        EndDrawing();
    }

    UnloadTexture(map);
    
}
