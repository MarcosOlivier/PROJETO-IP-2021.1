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
    Texture2D character = LoadTexture("texturas/SpriteSheetRight.png");  // CARREGA A TEXTURA

    Rectangle frameRec = {0.0f, 0.0f, (float)character.width/4 ,(float)character.height}; //RECORTA O PNG DA TEXTURA  EM RETANGULOS(/4 PORQUE SÃO 4 FRAMES DE ANIMACAO NO MEU EXEMPLO)
    Rectangle frameRecXInverted = {0.0f, 0.0f, (float)-character.width/4 ,(float)character.height}; // ´´ E ESPELHA O RESULTADO  NO EIXO X PARA DAR IMPRESSÃO QUE ESTÁ ANDANDO P ESQUERDA

     SetTargetFPS(60);

     while(!WindowShouldClose()){
         framesCounter ++;

        if(IsKeyDown(KEY_RIGHT)){
            direction = 1;
            position.x += moveX;
            if(framesCounter >= (60/frameSpeed)){  // VELOCIDADE DO FRAME(QUANTOS FRAMES VÃO PASSAR POR SEGUNDO)
                framesCounter = 0; //CADA FRAME É UM RETANGULO(PEDAÇO DO PNG)
                currentframe++;
                if(currentframe>4) // QUANDO CHEGAR NO ULTIMO FRAME VOLTA PRO PRIMEIRO(LOOP)
                currentframe=0;
                frameRec.x = (float)currentframe*(float)character.width/4;   //ASSOCIA UM NÚMERO A UM RETÂNGULO RECORTADO       
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
                framesCounter = 0; //
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
            DrawTextureRec(character, frameRecXInverted, position, RAYWHITE); // DESENHA A TEXTURA ESPELHADA
        }
        else
            DrawTextureRec(character, frameRec, position, RAYWHITE); // DESENHA A TEXTURA NORMAL
       
        EndDrawing();
     }
        UnloadTexture(character); //DESCARREGA A TEXTURA DA MEMÓRIA
        
        CloseWindow();
     return 0;
}
