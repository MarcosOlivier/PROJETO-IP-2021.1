#include "raylib.h"

const int screenWidth = 1080;
const int screenHeight = 720;

typedef enum ShootDirection {CIMA, BAIXO, DIREITA, ESQUERDA} ShootDirection;
typedef enum GameScreen {TITLE, GAMEPLAY, CREDITS} GameScreen;

typedef struct Inimigo{
    Rectangle hitbox;       //hitbox do inimigo
    bool vivo;              //Saber o estado do inimigo (vivo ou morto), precisamos do codigo da BALA. inimigo[i].vivo = vivo. !inimigo[i].vivo = morto;
    Color cor;              //Cor da hitbox do inimigo (BLANK para ficar transparente)(hitbox)
} Inimigo;

typedef struct moeda{
    Rectangle hitbox;       //Hitbox da moeda
    bool vivo;              //Saber se a moeda existe
    Color cor;              //Cor da hitbox da moeda (BLANK para ficar transparente)
    Vector2 position;
} Moeda;

typedef struct Player
{
    Vector2 position;      //posição do player
    Vector2 speed;
    Rectangle rectangle;
} Player;

typedef struct Shoot
{
    Vector2 position;
    Vector2 speed;
    bool active;
    Color color;
    ShootDirection direction;
    Rectangle Hitbox;

} Shoot;
