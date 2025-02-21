#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include "animation.h"
#include "bomberman.h"
#include "bomb.h"
#include "screens.h"
#include "textures.h"
 
// GLOBAL VARIABLES
static float accumulatedTime_1 = 0.0f;
static float accumulatedTime_2 = 0.0f;
static float accumlatedTimeBomb[2] = {0.0f};
static float accumulatedTimeExp[2] = {0.0f};
// GLOBAL FUNCTIONS DECLARATION

/////////////////////////////////////////////// 

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Teste");

	// Initalizing audio device
	InitAudioDevice();

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	// Loading the textures
	LoadBombermanTextures();
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
		.position = {0+BLOCK_SIZE+10,0+BLOCK_SIZE+10},
		.alive = true,
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
		.position = {SCREEN_WIDTH-BLOCK_SIZE,0},
		.alive = true,
		.bombermanText = black_bomberman_texture_left	
	};
	// Load a Music from the resources directory
	Music battle_music = LoadMusicStream("Naruto_Main_Theme.mp3");
	// Play Music
	PlayMusicStream(battle_music);
	// Setting Frame rate
	SetTargetFPS(60);
	// game loop
	while (!WindowShouldClose()) // run the loop untill the user presses ESCAPE or presses the Close button on the window
	{ 	
		// update the Game
		UpdateMusicStream(battle_music);

		SpriteAnimationUpdate(&player_1.bombermanAnimation, &accumulatedTime_1);
		SpriteAnimationUpdate(&player_2.bombermanAnimation, &accumulatedTime_2);

		UpdateMovement_1(&player_1);
		UpdateMovement_2(&player_2);

		if(IsKeyPressed(KEY_ENTER))
		{
			if(!player_1.bomb.isActive) player_1.bomb = PlaceBomb(player_1.position);
		}
		UpdateBomb(&player_1.bomb, &accumlatedTimeBomb[0], &accumulatedTimeExp[0]);

		if(IsKeyPressed(KEY_SPACE)) 
		{
			if(!player_2.bomb.isActive) player_2.bomb = PlaceBomb(player_2.position);
		}
		UpdateBomb(&player_2.bomb, &accumlatedTimeBomb[1], &accumulatedTimeExp[1]);
		// drawing the Game
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawMap();
		DrawGame(player_1, player_2);
		DrawBomb(&player_1.bomb);
		DrawBomb(&player_2.bomb);
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}
	// cleanup
	// unload our texture so it can be cleaned up
	UnloadBombermanTextures();
	// unload our sound
	UnloadMusicStream(battle_music);
	// destroy the window and cleanup the OpenGL context
	CloseAudioDevice();
	CloseWindow();
	return 0;
}

// GLOBAL FUNCTIONS
////////////	FUNCTIONS TO DEAL WITH BOMBS ARRAY	///////////

/////////////////////////////////////////////////////////