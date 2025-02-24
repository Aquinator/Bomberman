#include "map.h"


Texture grass;
Texture brick;
Texture stone;
Texture upper_grass;

// Create the TileMap (15x15 for this example)
int tileMap[MAP_HEIGHT][MAP_WIDTH] =
{
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 2},
    {2, 0, 2, 1, 2, 1, 2, 1, 2, 0, 2, 1, 2, 1, 2, 0, 2, 0, 2, 1, 2, 1, 2, 0, 2},
    {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 2},
    {2, 1, 2, 0, 2, 1, 2, 0, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2},
    {2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 2},
    {2, 1, 2, 1, 2, 0, 2, 1, 2, 1, 2, 1, 2, 1, 2, 0, 2, 1, 2, 1, 2, 1, 2, 1, 2},
    {2, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 2},
    {2, 1, 2, 1, 2, 1, 2, 0, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2},
    {2, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 2},
    {2, 1, 2, 0, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 0, 2, 1, 2, 1, 2, 1, 2},
    {2, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 2},
    {2, 0, 2, 0, 2, 1, 2, 0, 2, 1, 2, 1, 2, 0, 2, 1, 2, 1, 2, 0, 2, 1, 2, 0, 2},
    {2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2},
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

bool CollisionMap(Rectangle playerRect)
{
    for (int i = 0; i < MAP_HEIGHT; i++) 
    {
        for (int j = 0; j < MAP_WIDTH; j++) 
        {
            if (tileMap[i][j] == BRICK || tileMap[i][j] == STONE) 
            {
                if (CheckCollisionRecs(playerRect, RecMap[i][j])) return true; 
            }
        }
    }
    return false;
}

bool CheckCrossExplosion(int x, int y)
{
    // Check if any of the tiles in the cross explosion are BRICK
    return (tileMap[x-1][y] == BRICK || tileMap[x][y] == BRICK || tileMap[x+1][y] == BRICK 
            || tileMap[x][y-1] == BRICK || tileMap[x][y+1] == BRICK);
}

void DestroyMap(Vector2 Position)
{
    // Calculate the x and y indices for the tile based on the bomb position
    int x = (int)(Position.y / BLOCK_SIZE);
    int y = (int)(Position.x / BLOCK_SIZE);

    // Check for BRICK tiles in the cross-shaped area
    if (CheckCrossExplosion(x, y))
    {
        // Loop through the vertical positions
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (tileMap[x][j] == BRICK)
                tileMap[x][j] = GRASS;  // Change BRICK to GRASS
        }

        // Loop through the horizontal positions
        for (int i = x - 1; i <= x + 1; i++) 
        {
            if (tileMap[i][y] == BRICK)
                tileMap[i][y] = GRASS;  // Change BRICK to GRASS
        }
    }
}

