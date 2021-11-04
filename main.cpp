#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

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

    //instance of prop
    Prop rock{Vector2{}, LoadTexture("nature_tileset/Rock.png")};

    //Game loop
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.0f);

        //draw map
        DrawTextureEx(map, mapPos, 0.0f, mapScale, WHITE);
        
        //draw prop
        rock.Render(knight.getWorldPos());

        //update knight
        knight.tick(GetFrameTime());
        //check map bounds
        if(knight.getWorldPos().x < 0.0f 
            || knight.getWorldPos().y < 0.0f 
            || knight.getWorldPos().x + windowWidth > map.width * mapScale
            || knight.getWorldPos().y + windowHeight > map.height * mapScale
        )
        {
            knight.undoMovement();
        }
       

        EndDrawing();
    }

    UnloadTexture(map);
    
}
