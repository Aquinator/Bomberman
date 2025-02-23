#include "screens.h"
#include "bomberman.h"
#include "bomb.h"

//declaring the textures

Texture white_bomberman_texture_right;
Texture white_bomberman_texture_left;
Texture white_bomberman_texture_front;
Texture white_bomberman_texture_back;

Texture black_bomberman_texture_right;
Texture black_bomberman_texture_left;
Texture black_bomberman_texture_front;
Texture black_bomberman_texture_back;

// Loading textures from the resources directory
void LoadTextures(void)
{
    white_bomberman_texture_right = LoadTexture("white_bomberman_right.png");
    white_bomberman_texture_left = LoadTexture("white_bomberman_left.png");
    white_bomberman_texture_front = LoadTexture("white_bomberman_front.png");
    white_bomberman_texture_back = LoadTexture("white_bomberman_back.png");

	black_bomberman_texture_right = LoadTexture("black_bomberman_right.png");
    black_bomberman_texture_left = LoadTexture("black_bomberman_left.png");
    black_bomberman_texture_front = LoadTexture("black_bomberman_front.png");
    black_bomberman_texture_back = LoadTexture("black_bomberman_back.png");

	bomb_texture = LoadTexture("bomb.png");
	explosion_texture = LoadTexture("explosion.png");

	grass = LoadTexture("block_grass.png");
	brick = LoadTexture("block_brick.png");
	stone = LoadTexture("block_stone.png");
	upper_grass = LoadTexture("block_upper_grass.png");
}
// Unloading the textures from the memory
void UnloadTextures(void)
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

	UnloadTexture(grass);
    UnloadTexture(brick);
	UnloadTexture(stone);
	UnloadTexture(upper_grass);
}

void UpdatePlayer_1(Bomberman *player)
{
	Rectangle ghost; // rectangle representing the player at this potential next position. 
    if(IsKeyDown(KEY_RIGHT))
		{
			player->bombermanText = white_bomberman_texture_right;
			ghost = (Rectangle){player->position.x, player->position.y, BOMBERMAN_WIDTH/2, BOMBERMAN_HEIGHT/2};
			ghost.x += BOMBERMAN_SPEED;
			if (!CollisionMap(ghost)) //update movement only if there will be no collisions
        	{
            player->position.x += BOMBERMAN_SPEED; 
			SpriteAnimationShouldRepeat(&player->bombermanAnimation);		
			}
		}
		if(IsKeyDown(KEY_LEFT))
		{
			player->bombermanText = white_bomberman_texture_left;
			ghost = (Rectangle){player->position.x - (BOMBERMAN_WIDTH/2), player->position.y, BOMBERMAN_WIDTH/2, BOMBERMAN_HEIGHT/2};
			ghost.x -= BOMBERMAN_SPEED;
			if (!CollisionMap(ghost)) 
        	{
            player->position.x -= BOMBERMAN_SPEED; 
			SpriteAnimationShouldRepeat(&player->bombermanAnimation);		
			}
		}
		if(IsKeyDown(KEY_DOWN))
		{
			player->bombermanText = white_bomberman_texture_front;
			ghost = (Rectangle){player->position.x, player->position.y, BOMBERMAN_WIDTH/2, BOMBERMAN_HEIGHT/2};
			ghost.y += BOMBERMAN_SPEED;
			if (!CollisionMap(ghost)) 
        	{
            player->position.y += BOMBERMAN_SPEED; 
			SpriteAnimationShouldRepeat(&player->bombermanAnimation);		
			}
		}
		if(IsKeyDown(KEY_UP))
		{
			player->bombermanText = white_bomberman_texture_back;
			ghost = (Rectangle){player->position.x, player->position.y - 8, BOMBERMAN_WIDTH/2, BOMBERMAN_HEIGHT/2};
			ghost.y -= BOMBERMAN_SPEED;
			if (!CollisionMap(ghost)) 
        	{
            player->position.y -= BOMBERMAN_SPEED; 
			SpriteAnimationShouldRepeat(&player->bombermanAnimation);		
			}
		}
		if(IsKeyPressed(KEY_ENTER)) //place a bomb at the bomberman position
		{
			if(!player->bomb.isActive) player->bomb = PlaceBomb(player->position);
		}
}



void UpdatePlayer_2(Bomberman *player)
{
	Rectangle ghost; // rectangle representing the player at this potential next position. 
    if(IsKeyDown(KEY_D))
		{
			player->bombermanText = black_bomberman_texture_right;
			ghost = (Rectangle){player->position.x, player->position.y, BOMBERMAN_WIDTH/2, BOMBERMAN_HEIGHT/2};
			ghost.x += BOMBERMAN_SPEED;
			if (!CollisionMap(ghost))
        	{
            player->position.x += BOMBERMAN_SPEED; 
			SpriteAnimationShouldRepeat(&player->bombermanAnimation);		
			}
		}
		if(IsKeyDown(KEY_A))
		{
			player->bombermanText = black_bomberman_texture_left;
			ghost = (Rectangle){player->position.x - (BOMBERMAN_WIDTH/2), player->position.y, BOMBERMAN_WIDTH/2, BOMBERMAN_HEIGHT/2};
			ghost.x -= BOMBERMAN_SPEED;
			if (!CollisionMap(ghost)) 
        	{
            player->position.x -= BOMBERMAN_SPEED; 
			SpriteAnimationShouldRepeat(&player->bombermanAnimation);		
			}
		}
		if(IsKeyDown(KEY_S))
		{
			player->bombermanText = black_bomberman_texture_front;
			ghost = (Rectangle){player->position.x, player->position.y, BOMBERMAN_WIDTH/2, BOMBERMAN_HEIGHT/2};
			ghost.y += BOMBERMAN_SPEED;
			if (!CollisionMap(ghost)) 
        	{
            player->position.y += BOMBERMAN_SPEED; 
			SpriteAnimationShouldRepeat(&player->bombermanAnimation);		
			}
		}
		if(IsKeyDown(KEY_W))
		{
			player->bombermanText = black_bomberman_texture_back;
			ghost = (Rectangle){player->position.x, player->position.y - 8, BOMBERMAN_WIDTH/2, BOMBERMAN_HEIGHT/2};
			ghost.y -= BOMBERMAN_SPEED;
			if (!CollisionMap(ghost)) 
        	{
            player->position.y -= BOMBERMAN_SPEED; 
			SpriteAnimationShouldRepeat(&player->bombermanAnimation);		
			}
		}
		if(IsKeyPressed(KEY_SPACE)) 
		{
			if(!player->bomb.isActive) player->bomb = PlaceBomb(player->position);
		}
}

void DrawBomberman(Bomberman player_1, Bomberman player_2)
{
	Rectangle playerRec_1 = SpriteAnimationFrame(&player_1.bombermanAnimation, BOMBERMAN_MOVEMENT_SPRITE,
	BOMBERMAN_HEIGHT, BOMBERMAN_WIDTH);
	player_1.hitbox = (Rectangle){player_1.position.x, player_1.position.y, BOMBERMAN_WIDTH, BOMBERMAN_HEIGHT};
	
	DrawTexturePro(player_1.bombermanText, playerRec_1, player_1.hitbox, 
	(Vector2){BOMBERMAN_WIDTH/2, BOMBERMAN_HEIGHT/2},0.0, WHITE);
	
	Rectangle playerRec_2 = SpriteAnimationFrame(&player_2.bombermanAnimation, BOMBERMAN_MOVEMENT_SPRITE,
	BOMBERMAN_HEIGHT, BOMBERMAN_WIDTH);
	player_2.hitbox = (Rectangle){player_2.position.x, player_2.position.y, BOMBERMAN_WIDTH, BOMBERMAN_HEIGHT};

	DrawTexturePro(player_2.bombermanText, playerRec_2, player_2.hitbox, 
	(Vector2){BOMBERMAN_WIDTH/2, BOMBERMAN_HEIGHT/2},0.0, WHITE);
}
