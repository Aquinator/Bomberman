#include "raylib.h"

#include "screens.h"
#include "bomberman.h"
#include "bomb.h"

extern Rectangle RecMap [MAP_HEIGHT][MAP_WIDTH];

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
void LoadBombermanTextures(void)
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

	UnloadTexture(grass);
    UnloadTexture(brick);
	UnloadTexture(stone);
	UnloadTexture(upper_grass);
}

void UpdateMovement_1(Bomberman *player)
{
    if(IsKeyDown(KEY_RIGHT))
		{
			player->bombermanText = white_bomberman_texture_right;
			player->position.x += 2;
			SpriteAnimationShouldRepeat(&player->bombermanAnimation);		
		}
			if (player->position.x + (BOMBERMAN_WIDTH/2)>= SCREEN_WIDTH)
				player->position.x = SCREEN_WIDTH - (BOMBERMAN_WIDTH/2);

		if(IsKeyDown(KEY_LEFT))
		{
			player->bombermanText = white_bomberman_texture_left;
			player->position.x -= 2;
			SpriteAnimationShouldRepeat(&player->bombermanAnimation);
		}
			if ((player->position.x - (BOMBERMAN_WIDTH/2)) <= 0)
				player->position.x = (BOMBERMAN_WIDTH/2);

		if(IsKeyDown(KEY_DOWN))
		{
			player->bombermanText = white_bomberman_texture_front;
			player->position.y += 2;
			SpriteAnimationShouldRepeat(&player->bombermanAnimation);
		}
			if (player->position.y + (BOMBERMAN_HEIGHT/2)>= SCREEN_HEIGHT)
				player->position.y = SCREEN_HEIGHT - (BOMBERMAN_HEIGHT/2);

		if(IsKeyDown(KEY_UP))
		{
			player->bombermanText = white_bomberman_texture_back;
			player->position.y -= 2;
			SpriteAnimationShouldRepeat(&player->bombermanAnimation);
		}
			if (player->position.y - (BOMBERMAN_HEIGHT/2) <= 0)
				player->position.y = (BOMBERMAN_HEIGHT/2);
}


void UpdateMovement_2(Bomberman *player)
{
    if(IsKeyDown(KEY_D))
		{
			player->bombermanText = black_bomberman_texture_right;
			player->position.x += 2;
			SpriteAnimationShouldRepeat(&player->bombermanAnimation);		
		}
			if (player->position.x + (BOMBERMAN_WIDTH/2)>= SCREEN_WIDTH)
				player->position.x = SCREEN_WIDTH - (BOMBERMAN_WIDTH/2);

		if(IsKeyDown(KEY_A))
		{
			player->bombermanText = black_bomberman_texture_left;
			player->position.x -= 2;
			SpriteAnimationShouldRepeat(&player->bombermanAnimation);
		}
			if ((player->position.x - (BOMBERMAN_WIDTH/2)) <= 0)
				player->position.x = (BOMBERMAN_WIDTH/2);

		if(IsKeyDown(KEY_S))
		{
			player->bombermanText = black_bomberman_texture_front;
			player->position.y += 2;
			SpriteAnimationShouldRepeat(&player->bombermanAnimation);
		}
			if (player->position.y + (BOMBERMAN_HEIGHT/2)>= SCREEN_HEIGHT)
				player->position.y = SCREEN_HEIGHT - (BOMBERMAN_HEIGHT/2);

		if(IsKeyDown(KEY_W))
		{
			player->bombermanText = black_bomberman_texture_back;
			player->position.y -= 2;
			SpriteAnimationShouldRepeat(&player->bombermanAnimation);
		}
			if (player->position.y - (BOMBERMAN_HEIGHT/2) <= 0)
				player->position.y = (BOMBERMAN_HEIGHT/2);
}

void DrawGame(Bomberman player_1, Bomberman player_2)
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
