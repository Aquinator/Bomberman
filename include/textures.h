#ifndef ANIMATION_H_
#define ANIMATION_H_


#include "raylib.h"

Texture white_bomberman_texture_right;
Texture white_bomberman_texture_left;
Texture white_bomberman_texture_front;
Texture white_bomberman_texture_back;

Texture black_bomberman_texture_right;
Texture black_bomberman_texture_left;
Texture black_bomberman_texture_front;
Texture black_bomberman_texture_back;

Texture bomb_texture;


void LoadBombermanTextures(void)
{
    white_bomberman_texture_right = LoadTexture("bomberman_branco_direita.png");
    white_bomberman_texture_left = LoadTexture("bomberman_branco_esquerda.png");
    white_bomberman_texture_front = LoadTexture("bomberman_branco_frente.png");
    white_bomberman_texture_back = LoadTexture("bomberman_branco_costas.png");

	black_bomberman_texture_right = LoadTexture("bomberman_preto_direita.png");
    black_bomberman_texture_left = LoadTexture("bomberman_preto_esquerda.png");
    black_bomberman_texture_front = LoadTexture("bomberman_preto_frente.png");
    black_bomberman_texture_back = LoadTexture("bomberman_preto_costas.png");

	bomb_texture = LoadTexture("bomb.png");
}

void UnloadBombermanTextures(void)
{
    UnloadTexture(white_bomberman_texture_back);
    UnloadTexture(white_bomberman_texture_front);
    UnloadTexture(white_bomberman_texture_left);
    UnloadTexture(white_bomberman_texture_right);

	UnloadTexture(black_bomberman_texture_back);
    UnloadTexture(black_bomberman_texture_front);
    UnloadTexture(black_bomberman_texture_left);
    UnloadTexture(black_bomberman_texture_right);

	UnloadTexture(bomb_texture);
}
#endif
