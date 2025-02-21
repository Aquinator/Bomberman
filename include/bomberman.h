#ifndef BOMBERMAN_H_
#define BOMBERMAN_H_

#include "raylib.h"

#include "animation.h"
#include "bomb.h"

#define BOMBERMAN_MOVEMENT_SPRITE 4
#define BOMBERMAN_WIDTH 32
#define BOMBERMAN_HEIGHT 48

//defining the textures to the compiler
extern Texture white_bomberman_texture_right;
extern Texture white_bomberman_texture_left;
extern Texture white_bomberman_texture_front;
extern Texture white_bomberman_texture_back;

extern Texture black_bomberman_texture_right;
extern Texture black_bomberman_texture_left;
extern Texture black_bomberman_texture_front;
extern Texture black_bomberman_texture_back;

typedef struct
{
    Vector2 position;
    Texture bombermanText;
    Animation bombermanAnimation;
    Rectangle hitbox;
    Bomb bomb;
    bool alive;
} Bomberman; 

void LoadBombermanTextures(void);

void UnloadBombermanTextures(void);

void UpdateMovement_1(Bomberman *player);

void UpdateMovement_2(Bomberman *player);

void DrawGame(Bomberman player_1, Bomberman player_2);

#endif