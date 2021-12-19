#include "raylib.h"
#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1

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
    Vector2 positionmoeda;
} Moeda;

Moeda moeda[100];           //Vetor de 100 moedas no mapa (Pode ser alterada  a quantidade)

int main(){
    const int screenWidth = 1080;
    const int screenLength = 720;

    int contmoedas=0; //relaciona o indice dos 5 inimigos com as moedas
    int dinheiros=0; // qtd de dinheiro do jogador  (pontuação)
    int currentframemoedas = 0;  //frame inicial da moeda
    int framesCountermoedas = 0; //contador de frames da moeda
    int frameSpeedmoedas = 15;   //velocidade de frames da moeda
    
    InitWindow(screenWidth, screenLength, "Bola");
    SetTargetFPS(60);
    Texture2D moedateste = LoadTexture("Sprites/moedateste.png");  // CARREGA A TEXTURA DA MOEDA
    Rectangle frameRecmoeda = {0.0f, 0.0f, (float)moedateste.width/6 ,(float)moedateste.height}; //RECORTA O PNG DA TEXTURA  EM RETANGULOS(6 frames na animacao)
    
    for(int i = 0; i < 5; i++){                         //Inicializando os inimigos
        inimigo[i].hitbox.x = GetRandomValue(0,1080);   //Em posiçoes aleatorias
        inimigo[i].hitbox.y = GetRandomValue(0,720);
        inimigo[i].hitbox.width = 10;                   //Largura e altura da hitbox dos inimigos
        inimigo[i].hitbox.height = 10;
        inimigo[i].vivo = true;                         //Estado dos inimigos (Vivo)
        inimigo[i].cor = RED;                           //Cor da hitbox dos inimigos(BLANK para ficar transparente)
    }
    for (int i = 0; i < 100; i++){                    // inicializando moedas
        moeda[i].hitbox.width = 12;                   //Largura e altura da hitbox das moedas
        moeda[i].hitbox.height = 18;
        moeda[i].cor = GOLD;
        moeda[i].vivo = false;
    }
        
    mouse.hitbox.width = 10;
    mouse.hitbox.height = 10;
    mouse.cor = BLUE;
    
    while (!WindowShouldClose())    
    {
        framesCountermoedas ++; //aumentar frames da moeda
        
        
        
        
        
        
        mouse.hitbox.x = GetMouseX();
        mouse.hitbox.y = GetMouseY();

        BeginDrawing();

            ClearBackground(BLACK);
    
            DrawRectangle(mouse.hitbox.x,mouse.hitbox.y,10,10,mouse.cor); //Botei as coordenadas do mouse por enquanto que não tem o sistema de movimentaçao polida
            DrawText(TextFormat("Dinheiros = %d",dinheiros),0,0,30,RED);
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
                if ((CheckCollisionRecs(mouse.hitbox,inimigo[i].hitbox))){ //fiz a colisão com o mouse enquanto nao tem o Tiro
                     moeda[contmoedas].hitbox.x = inimigo[i].hitbox.x -20;  // coloquei o -20 só para o teste, alterar faz a moeda spawna 
                     moeda[contmoedas].hitbox.y = inimigo[i].hitbox.y -20;  // em diferentes lugares
                     moeda[contmoedas].vivo = true;                         // coloca a moeda viva quando colidir com o inimigo
                     moeda[contmoedas].positionmoeda.x =moeda[contmoedas].hitbox.x -6; //colocar os sprites na colisão da moeda
                     moeda[contmoedas].positionmoeda.y =moeda[contmoedas].hitbox.y -34;
                     inimigo[i].hitbox.x += GetRandomValue(-1080,1080);     // prótotipo respawn dos inimigos
                     inimigo[i].hitbox.y += GetRandomValue(-1080,1080);     // joga os inimigos para longe da tela
                     contmoedas++;                                          // variavel que relaciona os 5 inimigos com indice das moedas
            }
            }
            
            if(framesCountermoedas >= (60/frameSpeedmoedas)){  // VELOCIDADE DO FRAME(QUANTOS FRAMES VÃO PASSAR POR SEGUNDO)
                framesCountermoedas = 0; //CADA FRAME É UM RETANGULO(PEDAÇO DO PNG)
                currentframemoedas++;
                if(currentframemoedas>6){ // QUANDO CHEGAR NO ULTIMO FRAME VOLTA PRO PRIMEIRO(LOOP)
                frameRecmoeda.x = (float)currentframemoedas*(float)moedateste.width/6;   //ASSOCIA UM NÚMERO A UM RETÂNGULO RECORTADO       
            }   
                
        }
            for (int i=0; i<100;i++ ){
            
                if (moeda[i].vivo)
                    DrawTextureRec(moedateste, frameRecmoeda, moeda[i].positionmoeda, GOLD);
    }
            
 
            for (int i =0; i<100;i++){       
                if((CheckCollisionRecs(mouse.hitbox,moeda[i].hitbox)) && moeda[i].vivo) { //checa colisão com moedas vivas
                    moeda[i].vivo = false; // "mata" a moeda
                    dinheiros += 10;        // adiciona valor ao score
                }
            }
            
            
            if (dinheiros >= 100) // Alterar quantidade de dinheiro necessário para ganhar
                    DrawText("Agora vc pode pagar o agiota que só aceita notas de 100",100,100,20,RED); //placeholder tela de ganhar o jogo
        EndDrawing();

    }
    UnloadTexture(moedateste); //DESCARREGA A TEXTURA DA MEMÓRIA
    CloseWindow();

    return 0;
}