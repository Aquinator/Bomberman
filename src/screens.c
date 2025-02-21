#include "raylib.h"
#include "screens.h"


// Define the size of the map
#define NUM_HOUSES 5  // Number of indestructible blocks to place randomly

Texture grass;
Texture brick;
Texture stone;
Texture upper_grass;

// Create the TileMap (15x15 for this example)
int tileMap[MAP_HEIGHT][MAP_WIDTH] =
{
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2},
    {2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2},
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
};

Rectangle RecMap [MAP_HEIGHT][MAP_WIDTH]; 

void DrawMap()
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            Vector2 blockPosition = {(float)(j * BLOCK_SIZE), (float)(i * BLOCK_SIZE)};
            RecMap[i][j] = (Rectangle){blockPosition.x, blockPosition.y, BLOCK_SIZE, BLOCK_SIZE};
                switch (tileMap[i][j])
                {
                    case GRASS:
                        DrawTexturePro(grass,(Rectangle){0,0,BLOCK_SIZE, BLOCK_SIZE},RecMap[i][j],
                        (Vector2){0,0},0.0, WHITE);
                        break;
                    case BRICK:
                       //DrawTextureRec(brick,(Rectangle){0,0,BLOCK_SIZE, BLOCK_SIZE},blockPosition,WHITE);
                        DrawTexturePro(brick,(Rectangle){0,0,BLOCK_SIZE, BLOCK_SIZE},RecMap[i][j],
                        (Vector2){0,0},0.0, WHITE);
                        break;
                    case STONE:
                        DrawTexturePro(stone,(Rectangle){0,0,BLOCK_SIZE, BLOCK_SIZE},RecMap[i][j],
                        (Vector2){0,0},0.0, WHITE);
                        break;
                    case UPPER_GRASS:
                        DrawTexturePro(upper_grass,(Rectangle){0,0,BLOCK_SIZE, BLOCK_SIZE},RecMap[i][j],
                        (Vector2){0,0},0.0, WHITE);  
                        break;
            }
        }
    }
}
