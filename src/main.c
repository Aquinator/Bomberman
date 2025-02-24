#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "animation.h"
#include "bomberman.h"
#include "bomb.h"
#include "map.h"
 
// GLOBAL VARIABLES
static float accumulatedTime_1 = 0.0f;
static float accumulatedTime_2 = 0.0f;
static float accumlatedTimeBomb[2] = {0.0f};
static float accumulatedTimeExp[2] = {0.0f};
// GLOBAL FUNCTIONS DECLARATIONS
void BombermanDeath(Bomb bomba, Bomberman *player);
void DrawVictory_2(void);
void DrawVictory_1(void);

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	// Create the window and OpenGL context
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bomberman");
	// Initalizing audio device
	InitAudioDevice();
	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	// Loading the textures
	LoadTextures();
	// Declaring the players
	Bomberman player_1 = 
	{
		.bombermanAnimation=
		{
			.first = 0,
			.last = 4,
			.curr = 0,
			.frameTimer = 0.1,
			.type = ONESHOT
		},
		.position = {BLOCK_SIZE+(BOMBERMAN_WIDTH/2),BLOCK_SIZE+8},
		.alive = true,
		.movement = true,
		.deathText = white_bomberman_texture_death,
		.bombermanText = white_bomberman_texture_right		
	};

	Bomberman player_2 = 
	{
		.bombermanAnimation=
		{
			.first = 0,
			.last = 4,
			.curr = 0,
			.frameTimer = 0.1,
			.type = ONESHOT
		},
		.position = {SCREEN_WIDTH-BLOCK_SIZE-(BOMBERMAN_WIDTH/2),BLOCK_SIZE+8},
		.alive = true,
		.movement = true,
		.deathText = black_bomberman_texture_death,
		.bombermanText = black_bomberman_texture_left	
	};
	// Load a Music from the resources directory
	Music battle_music = LoadMusicStream("Battle Mode_Happy.mp3");
	// Play Music
	PlayMusicStream(battle_music);
	// Setting Frame rate
	SetTargetFPS(60);
	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{ 	
		while((player_1.alive && player_2.alive) && !WindowShouldClose())
		{
		// update the Game
		UpdateMusicStream(battle_music);

		SpriteAnimationUpdate(&player_1.bombermanAnimation, &accumulatedTime_1);
		SpriteAnimationUpdate(&player_2.bombermanAnimation, &accumulatedTime_2);

		UpdatePlayer_1(&player_1);
		UpdatePlayer_2(&player_2);

		UpdateBomb(&player_1.bomb, &accumlatedTimeBomb[0], &accumulatedTimeExp[0]);
		UpdateBomb(&player_2.bomb, &accumlatedTimeBomb[1], &accumulatedTimeExp[1]);

		BombermanDeath(player_1.bomb, &player_2);
		BombermanDeath(player_2.bomb, &player_1);
		// drawing the Game
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawMap();
		DrawBomberman(player_1, player_2);
		DrawBomb(&player_1.bomb);
		DrawBomb(&player_2.bomb);
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
		}
		if(!player_1.alive)
		{
			ClearBackground(RAYWHITE);
			DrawVictory_2();
		}
		if(!player_2.alive)
		{
			ClearBackground(RAYWHITE);
			DrawVictory_1();
		}
	}
	// unload the resources 
	UnloadTextures();
	UnloadMusicStream(battle_music);
	// destroy the window and cleanup the OpenGL context
	CloseAudioDevice();
	CloseWindow();
	return 0;
}

// Global Function to check collision between the explosion and the player
void BombermanDeath(Bomb bomba, Bomberman *player)
{
	if(player->alive)
	{
		if(bomba.isExploding)
		{
			// Calculate the x and y indices for the tile
			int player_x = (int)(player->position.y / BLOCK_SIZE);
			int player_y = (int)(player->position.x / BLOCK_SIZE);
			int bomba_x = (int)(bomba.position.y / BLOCK_SIZE);
			int bomba_y = (int)(bomba.position.x / BLOCK_SIZE);
			// checking overlapping positions in a cross 
			if((player_x == (bomba_x - 1) && player_y == bomba_y) ||
			(player_x == bomba_x && player_y == bomba_y) ||
			(player_x == (bomba_x + 1) && player_y == bomba_y) ||
			(player_y == (bomba_y - 1) && player_x == bomba_x) ||
			(player_y == bomba_y && player_x == bomba_x) || 
			(player_y == (bomba_y + 1) && player_x == bomba_x))
			{
				// creating the death animation
			player->bombermanText = player->deathText; 
			player->bombermanAnimation.frameTimer = 0.75f;
			accumulatedTime_1 = 0.0f;
			accumulatedTime_2 = 0.0f;
			player->bombermanAnimation.curr = player->bombermanAnimation.first;
			player->movement = false;
			}
		}
	}
	// check if the death animation is complete before setting alive to false
	if( player->bombermanText.id == player->deathText.id )
	{
		if(player->bombermanAnimation.curr == player->bombermanAnimation.last)
		player->alive = false;
	}
}
// Functions to Draw a screen victory to the player 
void DrawVictory_2(void)
{
			BeginDrawing();
			ClearBackground(DARKGRAY);
			DrawTexturePro(victory, (Rectangle){0,0,162,53},
			(Rectangle){VICTORY_WIDTH, VICTORY_HEIGHT,648,212},(Vector2){0,0}, 0.0, WHITE);
			DrawTexturePro(black_bomberman_texture_victory, (Rectangle){0,0,95,125},
			(Rectangle){(SCREEN_WIDTH/2) - 190,(SCREEN_HEIGHT/2) -52 ,190,250},(Vector2){0,0}, 0.0, WHITE);
			EndDrawing();
}
void DrawVictory_1(void)
{
			BeginDrawing();
			ClearBackground(DARKGRAY);
			DrawTexturePro(victory, (Rectangle){0,0,162,53},
			(Rectangle){VICTORY_WIDTH, VICTORY_HEIGHT,648,212},(Vector2){0,0}, 0.0, WHITE);
			DrawTexturePro(white_bomberman_texture_victory, (Rectangle){0,0,95,125},
			(Rectangle){(SCREEN_WIDTH/2) - 190,(SCREEN_HEIGHT/2) -52 ,190,250},(Vector2){0,0}, 0.0, WHITE);
			EndDrawing();
}