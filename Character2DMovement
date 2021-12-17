#include "raylib.h"

#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1

int main(void){
    int currentframe = 0;

    int framesCounter = 0;
    int frameSpeed = 15;

    const int screenWidth = 800;
    const int screenHeight = 450;

    int characterX = 350.0f;
    int characterY = 280.0f;
    int moveX = 7;
    int moveY = 7;

    int direction;


    InitWindow(screenWidth, screenHeight, "making a character move ");
    Vector2 position = {characterX, characterY};
    Texture2D character = LoadTexture("texturas/SpriteSheetRight.png");

    Rectangle frameRec = {0.0f, 0.0f, (float)character.width/4 ,(float)character.height};
    Rectangle frameRecXInverted = {0.0f, 0.0f, (float)-character.width/4 ,(float)character.height};

     SetTargetFPS(60);

     while(!WindowShouldClose()){
         framesCounter ++;

        if(IsKeyDown(KEY_RIGHT)){
            direction = 1;
            position.x += moveX;
            if(framesCounter >= (60/frameSpeed)){
                framesCounter = 0;
                currentframe++;
                if(currentframe>4)
                currentframe=0;
                frameRec.x = (float)currentframe*(float)character.width/4;           
            }   
        }
        if(IsKeyDown(KEY_LEFT)){
            direction = 0;
            position.x -= moveX;
            if(framesCounter >= (60/frameSpeed)){
                framesCounter = 0;
                currentframe++;
                if(currentframe>4)
                currentframe=0;

                frameRecXInverted.x = (float)currentframe*(float)character.width/4;           
            }   
        }
        if(IsKeyDown(KEY_UP)){
            direction = direction;
            position.y -= moveY;
            if(framesCounter >= (60/frameSpeed)){
                framesCounter = 0;
                currentframe++;
                if(currentframe>4)
                currentframe=0;
                if(direction == 0)
                    frameRecXInverted.x = (float)currentframe*(float)character.width/4;   
                else
                    frameRec.x = (float)currentframe*(float)character.width/4;       
            }   
        }
        if(IsKeyDown(KEY_DOWN)){
            direction = direction;
            position.y += moveY;
            if(framesCounter >= (60/frameSpeed)){
                framesCounter = 0;
                currentframe++;
                if(currentframe>4)
                currentframe=0;
                if(direction == 0)
                    frameRecXInverted.x = (float)currentframe*(float)character.width/4;   
                else
                    frameRec.x = (float)currentframe*(float)character.width/4;       
            }   
        }
        BeginDrawing();

        ClearBackground(RAYWHITE);
        
        if((direction == 0)){
            DrawTextureRec(character, frameRecXInverted, position, RAYWHITE);
        }
        else
            DrawTextureRec(character, frameRec, position, RAYWHITE);
       
        EndDrawing();
     }
        UnloadTexture(character);
        
        CloseWindow();
     return 0;
}
