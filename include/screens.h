#ifndef SCREENS_H_
#define SCREENS_H_


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

#define MAP_WIDTH 25
#define MAP_HEIGHT 15

#define BLOCK_SIZE 32

extern Texture grass;
extern Texture brick;
extern Texture stone;
extern Texture upper_grass;

extern int tileMap[MAP_HEIGHT][MAP_WIDTH];

enum
{
    GRASS = 0,
    BRICK = 1,
    STONE = 2,
    UPPER_GRASS = 3
};

void DrawMap(void);


#endif