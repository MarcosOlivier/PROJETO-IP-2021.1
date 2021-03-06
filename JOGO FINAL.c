#include "raylib.h"

#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1
#define NUM_SHOOTS 99999

#define LIMITE_ESQUERDA -800
#define LIMITE_DIREITA 1600
#define LIMITE_CIMA -450
#define LIMITE_BAIXO 900
#define LIMITE_ZOOM_MAX 1.5f
#define LIMITE_ZOOM_MIN 0.3f

const int screenWidth = 800;
const int screenHeight = 450;

typedef enum ShootDirection {CIMA, BAIXO, DIREITA, ESQUERDA} ShootDirection;
typedef enum GameScreen {TITLE, GAMEPLAY, GAMEOVER, WIN} GameScreen;

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
    Rectangle hitbox;
    bool vivo;
} Player;


    static Shoot shoot[NUM_SHOOTS];
    static Player player;

    static int shootRate;
    int shootCounter = 0;
    ShootDirection shootDirection = DIREITA;


typedef struct Inimigo{
    Rectangle hitbox;       //hitbox do inimigo
    bool vivo;              //Saber o estado do inimigo (vivo ou morto), precisamos do codigo da BALA. inimigo[i].vivo = vivo. !inimigo[i].vivo = morto;
    Color cor;             //Cor da hitbox do inimigo (BLANK para ficar transparente)(hitbox)
} Inimigo;

Inimigo inimigo[50];

typedef struct moeda{
    Rectangle hitbox;       //Hitbox da moeda
    bool vivo;              //Saber se a moeda existe
    Color cor;              //Cor da hitbox da moeda (BLANK para ficar transparente)
    Vector2 positionmoeda;
} Moeda;

Moeda moeda[20];


//se sim, retorna 1. se não, retorna 0
int CheckButton(Vector2 mousePoint, Rectangle recButton, Sound clickSound) {
    
    if (CheckCollisionPointRec(mousePoint, recButton)) {
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) { 
            PlaySound(clickSound);
            return 1;
        }
    }
    return 0;
}

int contmoedas=0; //relaciona o indice dos 5 inimigos com as moedas
int dinheiros=0; // qtd de dinheiro do jogador  (pontuação)



int main(void) {
    InitWindow(screenWidth, screenHeight, "MataVerso");
    InitAudioDevice();

    int currentframe = 0;
    int direction; //(esquerda ou direita) serve para definir para onde o character está olhando

    int framesCounter = 0;
    int frameSpeed = 15;

    //CARREGAR TEXTURAS E SONS
    Texture2D button = LoadTexture("texturas\\newbutton.png");
    Texture2D backgroundTitle = LoadTexture("texturas\\backgroundMenu.png");

    Sound clickSound = LoadSound("texturas\\resourses_MenuClick.wav");
    Sound menusound = LoadSound("texturas\\y2meta.com-Nick-Cave-and-the-Bad-Seeds-Red-Right-Hand-Karaoke-Instrumental-Lyrics-_128-kbps_.wav");
    Sound gamesound = LoadSound("texturas\\Grimm_Hollow_Knight__The_Grimm_Troupe_160k.mp3");

    Texture2D character = LoadTexture("texturas\\Running.png");
    Texture2D backgroundGame = LoadTexture("texturas\\cenario.png");
    Texture2D win = LoadTexture("texturas\\avengers-hulk-agiota.png");
    Texture2D enemy = LoadTexture ("texturas\\NightThief.png");
    Texture2D coin = LoadTexture("texturas\\moedateste.png");
    Texture2D bullet = LoadTexture("texturas\\bullet.png");

    backgroundGame.height = backgroundGame.height/2.0f;
    backgroundGame.width = backgroundGame.width/2.0f;

    player.hitbox.x = 350.0f;  //INICIALIZA AS CARACTERISTICAS DO PERSONAGEM
    player.hitbox.y = 250.0f;
    player.hitbox.width = 20;
    player.hitbox.height = 20;
    player.speed.x = 4;
    player.speed.y = 4;
    player.position.x = player.hitbox.x;
    player.position.y = player.hitbox.y;

    Camera2D camera = { 0 };     //CARACTERISTICAS DA CAMERA
    camera.target = (Vector2) {player.position.x + 20, player.position.y + 20};
    camera.offset = (Vector2) {screenWidth/2.0f, screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.5f;

    for(int i = 0; i < 12; i++){                         //Inicializando os inimigos
        inimigo[i].hitbox.x = GetRandomValue(0,1080);   //Em posiçoes aleatorias
        inimigo[i].hitbox.y = GetRandomValue(0,720);
        inimigo[i].hitbox.width = 30;                   //Largura e altura da hitbox dos inimigos
        inimigo[i].hitbox.height = 30;
        inimigo[i].vivo = true;                         //Estado dos inimigos (Vivo)
        inimigo[i].cor = RED;                          //Cor da hitbox dos inimigos(BLANK para ficar transparente)
    }
    for (int i = 0; i < 100; i++){                    // inicializando moedas
         moeda[i].hitbox.width = 20;                   //Largura e altura da hitbox das moedas
        moeda[i].hitbox.height = 25;
        moeda[i].cor = GOLD;
        moeda[i].vivo = false;
    }

    for (int i = 0; i < NUM_SHOOTS; i++)  //INICIALIZA AS CARACTERISTICAS DA BALA
    {
        shoot[i].rect.x = player.hitbox.x;
        shoot[i].rect.y = player.hitbox.y;
        shoot[i].rect.width = 10;
        shoot[i].rect.height = 10;
        shoot[i].speed.x = 30;
        shoot[i].speed.y = 30;
        shoot[i].active = false;
        shoot[i].color = MAROON;
    }

    GameScreen currentScreen = TITLE;

    SetTargetFPS(60);

    //AJUSTE DE TEXTURAS
    button.height = button.height/3.0;
    button.width = button.width/3.0;
    backgroundTitle.height = screenHeight;
    backgroundTitle.width = screenWidth;
    backgroundGame.width = 3*backgroundGame.width;
    backgroundGame.height = 3*backgroundGame.height;
    win.width = backgroundGame.width;
    win.height = backgroundGame.height;
    enemy.height = enemy.height*1.5;
    enemy.width = enemy.width*1.5;
    bullet.height = bullet.height/18;
    bullet.width = bullet.width/18;

    SetSoundVolume(menusound, 0.4);

    SetSoundVolume(gamesound, 0.4);

    //Rectangle Bullet =  {0.0f, 0.0f, (float)bullet.width ,(float)bullet.height};

    Rectangle frameRec = {0.0f, 0.0f, (float)-character.width/8 ,(float)character.height/2};
    Rectangle frameRecXInverted = {0.0f, 0.0f, (float)character.width/8 ,(float)character.height/2};
    Rectangle enemyRec ={0.0f, 0.0f, (float)-enemy.width/8.2 ,(float)enemy.height};
    Rectangle enemyRecInverted = {0.0f, 0.0f, (float)enemy.width/10 ,(float)enemy.height};
    Rectangle coinRec = {0.0f, 0.0f, (float)coin.width/6 ,(float)coin.height};
    Rectangle bulletRec = {0.0f, 0.0f, (float)bullet.width ,(float)bullet.height};
    Rectangle bulletRecInverted =  {0.0f, 0.0f, (float)-bullet.width ,(float)bullet.height};
 

    //botao e mouse
    Vector2 mousePoint = { 0.0f, 0.0f };
    Rectangle recButtonTitle = {screenWidth/4.0f - button.width/2.0f, screenHeight/4.0f - button.height/2.0f, button.width, button.height};
    Rectangle recButtonGameplay = {screenWidth - 200, screenHeight - 90, button.width, button.height};

    //scroll do background do menu inicial
    float scrollTitleScreen = 0.0f;
    float velScroll = 0.5f;
    
    while (!WindowShouldClose())
    {
        mousePoint = GetMousePosition();

        player.position.x = player.hitbox.x - 15;
        player.position.y = player.hitbox.y - 5;

        switch(currentScreen)  
        {
            case TITLE:
            {
                scrollTitleScreen -= velScroll;
                if (scrollTitleScreen <= -screenWidth) scrollTitleScreen = 0.0f;

               if (CheckButton(mousePoint, recButtonTitle, clickSound)) currentScreen = GAMEPLAY;

               if(!IsSoundPlaying(menusound)) 
                    PlaySound(menusound);
            } break;

            case GAMEPLAY:
            {
                if (IsSoundPlaying(menusound)) StopSound(menusound);
                if (!IsSoundPlaying(gamesound)) PlaySound(gamesound);

                if(IsKeyDown(KEY_RIGHT)){  //MOVIMENTA O PERSONAGEM PRA DIREITA
                shootDirection = DIREITA;
                direction = 1;
                player.hitbox.x += player.speed.x;
                if (player.position.x >= LIMITE_DIREITA) player.position.x = LIMITE_DIREITA;
                if(framesCounter >= (60/frameSpeed)){
                    framesCounter = 0;
                    currentframe++;
                    if(currentframe>8) currentframe=0;
                    frameRec.x = (float)currentframe*(float)character.width/8;         
            }   
        }
                if(IsKeyDown(KEY_LEFT)){  //MOVIMENTA O PERSONAGEM PRA ESQUERDA
                    shootDirection = ESQUERDA;
                    direction = 0;
                    player.hitbox.x -= player.speed.x;
                    if (player.position.x <= LIMITE_ESQUERDA) player.position.x = LIMITE_ESQUERDA;
                    if(framesCounter >= (60/frameSpeed)){
                    framesCounter = 0;
                    currentframe++;
                    if(currentframe>8)
                    currentframe=0;

                    frameRecXInverted.x = (float)currentframe*(float)character.width/8;          
            }   
        }
                if(IsKeyDown(KEY_UP)){  //MOVIMENTA O PERSONAGEM PRA CIMA
                    shootDirection = CIMA;
                    direction = direction;
                    player.hitbox.y -= player.speed.y;
                    if (player.position.y <= LIMITE_CIMA) player.position.y = LIMITE_CIMA;
                    if(framesCounter >= (60/frameSpeed)){
                        framesCounter = 0;
                        currentframe++;
                        if(currentframe>8)
                        currentframe=0;
                        if(shootDirection == 0)
                            frameRecXInverted.x = (float)currentframe*(float)character.width/8; 
                        else
                            frameRec.x = (float)currentframe*(float)character.width/8;       
                    }   
                }
                if(IsKeyDown(KEY_DOWN)){ //MOVIMENTA O PERSONAGEM PRA BAIXO
                    shootDirection = BAIXO;
                    direction = direction;
                    player.hitbox.y  += player.speed.y;
                    if (player.position.y >= LIMITE_BAIXO) player.position.y = LIMITE_BAIXO;
                    if(framesCounter >= (60/frameSpeed)){
                        framesCounter = 0;
                        currentframe++;
                        if(currentframe>8)
                        currentframe=0;
                        if(direction == 0)
                            frameRecXInverted.x = (float)currentframe*(float)character.width/8;   
                        else
                            frameRec.x = (float)currentframe*(float)character.width/8;       
                    }
            }
            if (IsKeyDown(KEY_SPACE))
    { 
            
        shootRate += 4;
        shootCounter++;
        for (int i = 0; i < NUM_SHOOTS; i++)
        {
            if (!shoot[i].active && shootRate % 40 == 0) //LIMITA A QUANTIDADE DE BALAS/SEG
            {
                shoot[i].rect.x = player.hitbox.x -5; //SPAWNA A BALA NESSAS COORDENADAS 
                shoot[i].rect.y = player.hitbox.y;
                shoot[i].active = true;
                shoot[i].direction = shootDirection;        
                break;
            }
        }
    }

                camera.target = (Vector2) {player.position.x, player.position.y};
                camera.zoom += ((float)GetMouseWheelMove()*0.05f);

                if (camera.zoom > 3.0f) camera.zoom = 3.0f;
                else if (camera.zoom < 0.1f) camera.zoom = 0.1f;

                if (CheckButton(mousePoint, recButtonGameplay, clickSound)) currentScreen = TITLE;

                for(int j = 0; j < 5; j++){
                if(CheckCollisionRecs(player.hitbox, inimigo[j].hitbox)){
                            player.vivo = false;
                            currentScreen = GAMEOVER;
                        } 
                }

                if(dinheiros >= 100){
                    currentScreen = WIN;
                }

            } break;
            default: break;
        }

        BeginDrawing();

            ClearBackground(BLACK);

            switch(currentScreen)
            {
                case TITLE:
                {
                    ClearBackground(BLACK);
                    DrawTexture(backgroundTitle, scrollTitleScreen, 0, WHITE);
                    DrawTexture(backgroundTitle, scrollTitleScreen + screenWidth, 0, WHITE);
                    DrawTexture(button, screenWidth/4.0f - button.width/2.0f, screenHeight/4.0f - button.height/2.0f, RAYWHITE);
                    DrawText("PLAY", screenWidth/4.0f + button.width/1.5f, screenHeight/4.0f - button.height/4.0f, button.height/2, BLACK);
                    DrawText("Movimentação: Setas do teclado", 200, 250, 30, BLACK);
                    DrawText("Atirar: Espaço", 200, 220, 30, BLACK);
                } break;
                case GAMEPLAY:
                {    
                BeginMode2D(camera);

                //desenhando background 9 vezes
                for (int i = -1; i < 2; i++) {
                    for (int j = -1; j < 2; j++) {
                        DrawTexture(backgroundGame, i*backgroundGame.width, j*backgroundGame.height, WHITE);
                    }
                }
                
                for(int i = 0; i < 12; i++){
                if (inimigo[i].vivo){ //Aproxima o coordenada da hitbox do inimigo ate a do player
                    if(player.position.x > inimigo[i].hitbox.x)
                        inimigo[i].hitbox.x += 1.5;
                    if(player.position.x < inimigo[i].hitbox.x)
                        inimigo[i].hitbox.x -= 1.5;            // O 1 pode ser alterado pra mudar a velocidade dos inimigos
                    if(player.position.y > inimigo[i].hitbox.y)
                        inimigo[i].hitbox.y += 1.5;
                    if(player.position.y < inimigo[i].hitbox.y)
                        inimigo[i].hitbox.y -= 1.5;

                        if ((inimigo[i].vivo) && (player.position.x >= inimigo[i].hitbox.x)){
                    DrawTextureRec(enemy, enemyRecInverted, (Vector2) {inimigo[i].hitbox.x, inimigo[i].hitbox.y} , WHITE);
                    }

                    if ((inimigo[i].vivo) && (player.position.x < inimigo[i].hitbox.x)){
                        DrawTextureRec(enemy, enemyRec, (Vector2) {inimigo[i].hitbox.x, inimigo[i].hitbox.y} , WHITE);
                        
                    }
                }
            }                                             
        

            for(int i = 0; i <NUM_SHOOTS; i++){ //colisao bala - inimigo
                for (int j = 0; j < 12; j++){
                    if ((CheckCollisionRecs(shoot[j].rect,inimigo[j].hitbox))){ 
                        moeda[contmoedas].hitbox.x = inimigo[j].hitbox.x -20;  // coloquei o -20 só para o teste, alterar faz a moeda spawna 
                        moeda[contmoedas].hitbox.y = inimigo[j].hitbox.y -20;  // em diferentes lugares
                        moeda[contmoedas].positionmoeda.x = moeda[contmoedas].hitbox.x;
                        moeda[contmoedas].positionmoeda.y = moeda[contmoedas].hitbox.y;
                        moeda[contmoedas].vivo = true;                         // coloca a moeda viva quando colidir com o inimigo
                        inimigo[j].hitbox.x += GetRandomValue(-1080,1080);     // prótotipo respawn dos inimigos
                        inimigo[j].hitbox.y += GetRandomValue(-1080,1080);     // joga os inimigos para longe da tela
                        contmoedas++;
                        if(contmoedas < 100){
                            contmoedas = 0;
                        }                                     
                    }
                }
            }

            for(int i = 0; i < 100; i++){           //desenhando a moeda na tela
            if ((moeda[i].vivo)){   
                    DrawTextureRec(coin, coinRec, (Vector2){moeda[i].hitbox.x, moeda[i].hitbox.y}, WHITE);
                }
            }
            for (int i =0; i<20;i++){      
                if((CheckCollisionRecs(player.hitbox,moeda[i].hitbox)) && moeda[i].vivo) { //checa colisão com moedas vivas
                    moeda[i].vivo = false; // "mata" a moeda
                    dinheiros += 10;        // adiciona valor ao score
                }

            }

                for (int i = 0; i < NUM_SHOOTS; i++){
            if (shoot[i].active){

                //MOVIMENTA A BALA 

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

                if (shoot[i].rect.x >= LIMITE_DIREITA || shoot[i].rect.x <= LIMITE_ESQUERDA ||shoot[i].rect.y >= LIMITE_BAIXO || shoot[i].rect.y <= LIMITE_CIMA){ //EXCLUI A BALA DEPOIS QUE SAI DA TELA
                    shoot[i].active = false;
                    shootRate = 0;
                }
            }
         }

                for (int i = 0; i < NUM_SHOOTS; i++){

                    if (shoot[i].active && shootDirection == CIMA)
                    DrawTextureRec(bullet, bulletRec, (Vector2) {shoot[i].rect.x, shoot[i].rect.y}, WHITE);

                    if (shoot[i].active && shootDirection == BAIXO)
                    DrawTextureRec(bullet, bulletRec, (Vector2) {shoot[i].rect.x, shoot[i].rect.y}, WHITE);

                    if (shoot[i].active && shootDirection == DIREITA)
                    DrawTextureRec(bullet, bulletRec, (Vector2) {shoot[i].rect.x, shoot[i].rect.y}, WHITE);

                    if (shoot[i].active && shootDirection == ESQUERDA)
                    DrawTextureRec(bullet, bulletRecInverted, (Vector2) {shoot[i].rect.x, shoot[i].rect.y}, WHITE);

            }

                if((direction == 0)){
                    DrawTextureRec(character, frameRecXInverted, (Vector2) {player.hitbox.x, player.hitbox.y}, RAYWHITE);
                    
                }
                else
                    DrawTextureRec(character, frameRec, player.position, RAYWHITE);

                EndMode2D();
                DrawText(TextFormat("Dinheiros = %d",dinheiros),0,0,30,RED);
                }
                break; 

            case GAMEOVER:
                {
                ClearBackground(BLACK);
                DrawText("GAME OVER", 50, 50, 40, RED);
                DrawText("Matheus gomes (mga3)", 200, 300, 15,RED);
                DrawText("Kelno Espírito Santo (kes)", 200, 280, 15,RED);
                DrawText("Caio Andrada (cab5)", 200, 260, 15, RED);
                DrawText("João Pedro (jpfs2)", 200, 240, 15,RED);
                DrawText("Marcos Oliveira (mvo)", 200, 220,15, RED);
                DrawText("Leandro Luiz (lllf)", 200, 200,15, RED);
                DrawText("Luis Henrique (lhol)", 200, 180,15, RED);
                DrawText("Joao Victor Alves (jvca)", 200, 160,15, RED);
                } break;

                case WIN:
                {
                DrawTexture(win, 0, 0, RAYWHITE);
                DrawText("YOU WIN", 50, 50, 40, GOLD);
                DrawText("Matheus gomes (mga3)", 100, 300, 15,GOLD);
                DrawText("Kelno Espírito Santo (kes)", 100, 280, 15,GOLD);
                DrawText("Caio Andrada (cab5)", 100, 260, 15, GOLD);
                DrawText("João Pedro (jpfs2)", 100, 240, 15,GOLD);
                DrawText("Marcos Oliveira (mvo)", 100, 220,15, GOLD);
                DrawText("Leandro Luiz (lllf)", 100, 200,15, GOLD);
                DrawText("Luis Henrique (lhol)", 100, 180,15, GOLD);
                DrawText("Joao Victor Alves (jvca)", 100, 160,15, GOLD);
                
                } break;
            

                default:
                
                break;
                    }

                if (dinheiros >= 100) // Alterar quantidade de dinheiro necessário para ganhar
                    DrawText("Agora você pode pagar o agiota que só aceita notas de 100",100,100,20,RED); //placeholder tela de ganhar o jogo
                EndDrawing();
    }

    //UNLOAD 
    UnloadTexture(button);
    UnloadTexture(backgroundTitle);
    UnloadTexture(character);
    UnloadTexture(backgroundGame);
    UnloadTexture(win);
    UnloadTexture(coin);
    UnloadTexture(bullet);
    UnloadSound(clickSound);
    UnloadSound(menusound);
    UnloadSound(gamesound);

    CloseWindow(); 
    return 0;
}
