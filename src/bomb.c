#include "bomb.h"
#include "animation.h"
#include "map.h"

Texture bomb_texture;
Texture explosion_texture;
extern Rectangle RecMap [MAP_HEIGHT][MAP_WIDTH]; //needed to check explosion collision

Bomb PlaceBomb(Vector2 Position)
{
    // Creates a bomb at the position parameter
    Bomb bomb =
    {
        .position = Position,
        .isActive = true,
        .bombTexture = bomb_texture,
        .lifeTime = 3.0f,
        .timer = 0.0f,
        .isExploding = false,
        .explosionTime = 0.5f,
        .bombAnimation =
        {
            .curr = 0,
            .first = 0,
            .last = BOMB_SPRITE,
            .frameTimer = 0.2f,
            .type = CONTINUOUS
        },
        .explosionAnimation = 
        {
            .curr = 0,
            .curr = 0,
            .last = EXPLOSION_SPRITE,
            .frameTimer = 0.1f,
            .type = ONESHOT
        }
    };
 return bomb;
}

void UpdateBomb(Bomb *bomb, float *bombAccumulatedTime, float *explosionAccumulatedTime) 
{
    if (bomb->isActive || bomb->isExploding) 
    {
        bomb->timer += GetFrameTime();
        // Update animations based on current state
        if (bomb->isActive) 
        {
            SpriteAnimationUpdate(&bomb->bombAnimation, bombAccumulatedTime);
            // Check if bomb should explode
            if (bomb->timer >= bomb->lifeTime)
            {
                bomb->isActive = false;
                bomb->isExploding = true;
                bomb->bombTexture = explosion_texture;
                bomb->timer = 0.0f;
            }
        }
        else if (bomb->isExploding) 
        {
            SpriteAnimationUpdate(&bomb->explosionAnimation, explosionAccumulatedTime);
            // Check if explosion should end
            if (bomb->timer >= bomb->explosionTime) 
            {
                bomb->isExploding = false;
            }
        }
    }
}

void DrawBomb(Bomb *bomb) 
{
    if (bomb->isActive) 
    {
        // Draw the bomb with animation
        Rectangle source = SpriteAnimationFrame(&bomb->bombAnimation, BOMB_SPRITE, BOMB_HEIGHT, BOMB_WIDTH);
        
        DrawTexturePro(bomb->bombTexture, source, (Rectangle){bomb->position.x, bomb->position.y,
            BOMB_WIDTH, BOMB_HEIGHT},
            (Vector2){(BOMB_WIDTH/2),(BOMB_HEIGHT/2)},0.0, WHITE);
                
    }
    else if (bomb->isExploding)
    {
        Rectangle source = SpriteAnimationFrame(&bomb->explosionAnimation, EXPLOSION_SPRITE, EXPLOSION_HEIGHT, EXPLOSION_WIDTH);
        bomb->bombHitbox = (Rectangle){bomb->position.x, bomb->position.y, EXPLOSION_WIDTH, EXPLOSION_HEIGHT};
        DestroyMap(bomb->position);
        for(int i = 0; i<4; i++)
        {
        DrawTexturePro(bomb->bombTexture, source,bomb->bombHitbox,
        (Vector2){(EXPLOSION_WIDTH/2), (EXPLOSION_Y_CENTER)}, 90*i, WHITE);
        }
    }
}



