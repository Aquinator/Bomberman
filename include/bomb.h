#ifndef BOMB_H_
#define BOMB_H_

#include "raylib.h"

#include "animation.h"

#define BOMB_WIDTH 32
#define BOMB_HEIGHT 36
#define BOMB_SPRITE 3

#define EXPLOSION_WIDTH 32
#define EXPLOSION_HEIGHT 96
#define EXPLOSION_SPRITE 4
#define EXPLOSION_Y_CENTER 80

#define MAX_BOMBS 5

extern Texture bomb_texture;
extern Texture explosion_texture;

typedef struct
{
    Vector2 position;      // Position of the bomb
    Texture2D bombTexture;    // Texture for the bomb
    float timer;          // Time elapsed since bomb was placed
    float lifeTime;       // Lifetime of the bomb
    float explosionTime;  // Duration of the explosion
    bool isActive;          // boolean to draw the bomb
    bool isExploding;        // boolean to draw the explosion
    Animation bombAnimation; // animation of the bomb
    Animation explosionAnimation; // animation of the explosion
    Rectangle bombHitbox;          // rectangle drawn in the screen
} Bomb;

Bomb PlaceBomb(Vector2 position);
void UpdateBomb(Bomb *bomb, float *bombAccumulatedTime, float *explosionAccumulatedTime);
void DrawBomb(Bomb *bomb);


#endif