#ifndef MAP_H_
#define MAP_H_

#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

#define VICTORY_WIDTH 76
#define VICTORY_HEIGHT 28

#define MAP_WIDTH 25
#define MAP_HEIGHT 15

#define BLOCK_SIZE 32

extern Texture grass;
extern Texture brick;
extern Texture stone;
extern Texture upper_grass;
extern Texture victory;

extern int tileMap[MAP_HEIGHT][MAP_WIDTH];

enum
{
    GRASS = 0,
    BRICK = 1,
    STONE = 2,
    UPPER_GRASS = 3
};

void DrawMap(void);
void DestroyMap(Vector2 Position);
bool CheckCrossExplosion(int x, int y);
bool CollisionMap(Rectangle playerRect);


#endif