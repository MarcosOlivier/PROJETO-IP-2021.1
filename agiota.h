// todos os structs que usamos no projeto organizado em uma file separada
// **********************************************************************

#include "raylib.h"

typedef struct Inimigo{
    Rectangle hitbox;       //hitbox do inimigo
    bool vivo;              //Saber o estado do inimigo (vivo ou morto), precisamos do codigo da BALA. inimigo[i].vivo = vivo. !inimigo[i].vivo = morto;
    Color cor;              //Cor da hitbox do inimigo (BLANK para ficar transparente)(hitbox)
} Inimigo;

typedef struct Mouse{
    Rectangle hitbox;       //Hitbox do inimigo
    Color cor;              //Cor da hitbox do player (BLANK para ficar transparente)
} Mouse;               //Struct do mouse (Podia ser substituida por uma struct rectangle pro codigo ficar mais polido)

typedef struct moeda{
    Rectangle hitbox;       //Hitbox da moeda
    bool vivo;              //Saber se a moeda existe
    Color cor;              //Cor da hitbox da moeda (BLANK para ficar transparente)
} Moeda;

typedef struct Player
{
    Vector2 position;
    Vector2 speed;
} Player;
