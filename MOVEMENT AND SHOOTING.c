#include "raylib.h"

#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1
#define NUM_SHOOTS 99999

typedef enum ShootDirection {CIMA, BAIXO, DIREITA, ESQUERDA} ShootDirection;

typedef struct Shoot
{
    Rectangle rect;
    Vector2 speed;
    bool active;
    Color color;
    ShootDirection direction;

} Shoot;

typedef struct Player  
{
    Vector2 position;
    Vector2 speed;
} Player;

    const int screenWidth = 800;  //DIZ O TAMANHO DA JANELA
    const int screenHeight = 450;

    static Shoot shoot[NUM_SHOOTS];
    static Player player;

    static int shootRate;
    int shootCounter = 0;
    ShootDirection shootDirection = DIREITA;

int main(void){
    int currentframe = 0;

    int framesCounter = 0;
    int frameSpeed = 15;

    player.position.x = 350.0f;  //INICIALIZA AS CARACTERISTICAS DO PERSONAGEM
    player.position.y = 250.0f;
    player.speed.x = 7;
    player.speed.y = 7;

     for (int i = 0; i < NUM_SHOOTS; i++)  //INICIALIZA AS CARACTERISTICAS DA BALA
    {
        shoot[i].rect.x = player.position.x;
        shoot[i].rect.y = player.position.y;
        shoot[i].rect.width = 10;
        shoot[i].rect.height = 5;
        shoot[i].speed.x = 10;
        shoot[i].speed.y = 10;
        shoot[i].active = false;
        shoot[i].color = MAROON;
    }

    int direction;
    
    InitWindow(screenWidth, screenHeight, "making a character move ");  //INICIALIZA A TELA

    Texture2D character = LoadTexture("resourses\\SpriteSheetRight.png");  //CARREGA A TEXTURA DO PERSONAGEM
    Rectangle frameRec = {0.0f, 0.0f, (float)character.width/4 ,(float)character.height};  //RECORTA A TEXTURA
    Rectangle frameRecXInverted = {0.0f, 0.0f, (float)-character.width/4 ,(float)character.height}; //ESPELHA A TEXTURA

     SetTargetFPS(60);

     while(!WindowShouldClose()){ //DETECTA SE A TELA FOI FECHADA OU SE APERTARAM ESC
         framesCounter ++;

        if(IsKeyDown(KEY_RIGHT)){  //MOVIMENTA O PERSONAGEM PRA DIREITA
            shootDirection = DIREITA;
            direction = 1;
            player.position.x += player.speed.x;
            if(framesCounter >= (60/frameSpeed)){
                framesCounter = 0;
                currentframe++;
                if(currentframe>4)
                currentframe=0;
                frameRec.x = (float)currentframe*(float)character.width/4;           
            }   
        }
        if(IsKeyDown(KEY_LEFT)){  //MOVIMENTA O PERSONAGEM PRA ESQUERDA
            shootDirection = ESQUERDA;
            direction = 0;
            player.position.x -= player.speed.x;
            if(framesCounter >= (60/frameSpeed)){
                framesCounter = 0;
                currentframe++;
                if(currentframe>4)
                currentframe=0;

                frameRecXInverted.x = (float)currentframe*(float)character.width/4;           
            }   
        }
        if(IsKeyDown(KEY_UP)){  //MOVIMENTA O PERSONAGEM PRA CIMA
            shootDirection = CIMA;
            player.position.y -= player.speed.y;
            if(framesCounter >= (60/frameSpeed)){
                framesCounter = 0;
                currentframe++;
                if(currentframe>4)
                currentframe=0;
                if(shootDirection == 0)
                    frameRecXInverted.x = (float)currentframe*(float)character.width/4;   
                else
                    frameRec.x = (float)currentframe*(float)character.width/4;       
            }   
        }
        if(IsKeyDown(KEY_DOWN)){ //MOVIMENTA O PERSONAGEM PRA BAIXO
            shootDirection = BAIXO;
            player.position.y  += player.speed.y;
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
      if (IsKeyDown(KEY_SPACE))
    {

        shootRate += 5;
        shootCounter++;
        for (int i = 0; i < NUM_SHOOTS; i++)
        {
            if (!shoot[i].active && shootRate % 40 == 0) //LIMITA A QUANTIDADE DE BALAS/SEG
            {
                shoot[i].rect.x = player.position.x + 50; //SPAWNA A BALA NESSAS COORDENADAS OLHANDO PARA A DIREITA
                shoot[i].rect.y = player.position.y+80;
                shoot[i].active = true;
                shoot[i].direction = shootDirection;
                break;
            }
        }
    }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (int i = 0; i < NUM_SHOOTS; i++){
            if (shoot[i].active){

                //shoot[i].rect.x += shoot[i].speed.x; //MOVIMENTA A BALA HORIZONTALMENTE

                switch (shoot[i].direction)
                {
                case CIMA:
                    shoot[i].rect.y -= shoot[i].speed.y;
                    break;
                
                case BAIXO:
                    shoot[i].rect.y += shoot[i].speed.y;
                    break;

                case DIREITA:
                    shoot[i].rect.x += shoot[i].speed.x;
                    break;

                case ESQUERDA:
                    shoot[i].rect.x -= shoot[i].speed.x;
                    break;

                default:
                    break;
                }

                if (shoot[i].rect.x >= 800){ //EXCLUI A BALA DEPOIS QUE SAI DA TELA
                    shoot[i].active = false;
                    shootRate = 0;
                }
            }
         }

        for (int i = 0; i < NUM_SHOOTS; i++){
        if (shoot[i].active)
            DrawRectangleRec(shoot[i].rect, shoot[i].color); //DESENHA A BALA
        }


        if((direction == 0)){
            DrawTextureRec(character, frameRecXInverted, player.position, RAYWHITE);
        }
        else
            DrawTextureRec(character, frameRec, player.position, RAYWHITE);
       
        EndDrawing();
    }
        UnloadTexture(character);
        
        CloseWindow();
     return 0;
}
