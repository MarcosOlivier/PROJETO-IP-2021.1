#include "raylib.h"

typedef struct Inimigo{
    Rectangle hitbox;       //hitbox do inimigo
    bool vivo;              //Saber o estado do inimigo (vivo ou morto), precisamos do codigo da BALA. inimigo[i].vivo = vivo. !inimigo[i].vivo = morto;
    Color cor;              //Cor da hitbox do inimigo (BLANK para ficar transparente)(hitbox)
} Inimigo;

Inimigo inimigo[5];

typedef struct Mouse{
    Rectangle hitbox;       //Hitbox do inimigo
    Color cor;              //Cor da hitbox do player (BLANK para ficar transparente)
} Mouse;

Mouse mouse;                //Struct do mouse (Podia ser substituida por uma struct rectangle pro codigo ficar mais polido)

typedef struct moeda{
    Rectangle hitbox;       //Hitbox da moeda
    bool vivo;              //Saber se a moeda existe
    Color cor;              //Cor da hitbox da moeda (BLANK para ficar transparente)
} Moeda;

Moeda moeda[100];           //Vetor de 100 moedas no mapa (Pode ser alterada  a quantidade)

int main(){
    const int screenWidth = 1920;
    const int screenLength = 1080;
    int cont = 0;
    
    InitWindow(screenWidth, screenLength, "Bola");
    SetTargetFPS(60);
    for(int i = 0; i < 5; i++){                         //Inicializando os inimigos
        inimigo[i].hitbox.x = GetRandomValue(0,1920);   //Em posiçoes aleatorias
        inimigo[i].hitbox.y = GetRandomValue(0,1080);
        inimigo[i].hitbox.width = 40;                   //Largura e altura da hitbox dos inimigos
        inimigo[i].hitbox.height = 40;
        inimigo[i].vivo = true;                         //Estado dos inimigos (Vivo)
        inimigo[i].cor = RED;                           //Cor da hitbox dos inimigos(BLANK para ficar transparente)
    }
    
    mouse.hitbox.width = 40;
    mouse.hitbox.height = 40;
    mouse.cor = BLUE;
    
    while (!WindowShouldClose())    
    {
        mouse.hitbox.x = GetMouseX();
        mouse.hitbox.y = GetMouseY();

        BeginDrawing();

            ClearBackground(BLACK);
    
            DrawRectangle(mouse.hitbox.x,mouse.hitbox.y,40,40,mouse.cor); //Botei as coordenadas do mouse por enquanto que não tem o sistema de movimentaçao polida

            for(int i = 0; i < 5; i++){
                if ((inimigo[i].vivo)){
                    DrawRectangleRec(inimigo[i].hitbox, inimigo[i].cor); //Desenha 5 quadrados em localizaçoes aleatorias, a ideia é deixar os quadrados invisiveis e
                }                                                        //botar a sprite do inimigo em cima. Preciso de ajuda pra colocar delay nos spawns se alguem souber
            
            }
            for(int i = 0; i < 5; i++){
                if (inimigo[i].vivo){ //Aproxima o coordenada da hitbox do inimigo ate a do player
                    if(mouse.hitbox.x > inimigo[i].hitbox.x)
                        inimigo[i].hitbox.x += 1;
                    if(mouse.hitbox.x < inimigo[i].hitbox.x)
                        inimigo[i].hitbox.x -= 1;            // O 1 pode ser alterado pra mudar a velocidade dos inimigos
                    if(mouse.hitbox.y > inimigo[i].hitbox.y)
                        inimigo[i].hitbox.y += 1;
                    if(mouse.hitbox.y < inimigo[i].hitbox.y)
                        inimigo[i].hitbox.y -= 1;
                }
                if ((CheckCollisionRecs(mouse.hitbox,inimigo[i].hitbox)) && (cont == 0)) //Checa colisao entre dois retangulos (Inimigo e player)
                    cont++; //Caso a colisao ocorra a tela de game over aparece
                if (cont > 0)
                    DrawText("Game Over",100,100,100,RED); //placeholder tela de game over tentar novamente.
                    
            }
            
        EndDrawing();

    }

    CloseWindow();

    return 0;
}
