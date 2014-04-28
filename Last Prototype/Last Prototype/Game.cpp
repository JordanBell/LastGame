#include "Game.h"
#include "SDL.h"
#include <time.h>
#include "WorldBuilder.h"
#include "Player.h"
#include "Environment.h"

Game* g_game = NULL;

Game::Game() : running(true)
{
	delta = 0;
	srand(time(NULL));
}

Game::~Game() { delete g_camera; }

void Game::init()
{
	// Initiailise the Environment and Player
	g_environment = new Environment(0, 0);
	WorldBuilder::build();
	g_player = new Player((int)(WORLD_WIDTH/2), (int)(WORLD_HEIGHT/2));

	// Add everything to the AllContainer
	g_camera = new Camera();
}

void Game::run()
{	
	init();

	while (running)
	{
		m_FPSTimer.start();

		// Triumvirate Game loop processes
		Update();
		Render();
		Poll();

		// Regulate the framerate, and save the delta time.
		delta = RegulateFrameRate();
	}

	delete this;
}

void Game::Update()
{
	HandleKeys();
	
	// Update the entities
	g_camera->update(delta);
}

void Game::HandleKeys()
{
	//Get the keystates
	Uint8 *keystates = SDL_GetKeyState(NULL);
	
		//WASD moves the player
		if (keystates[SDLK_w])	g_player->walk(UP);
		if (keystates[SDLK_s])	g_player->walk(DOWN);
		if (keystates[SDLK_a])	g_player->walk(LEFT);
		if (keystates[SDLK_d])	g_player->walk(RIGHT);

		// Toggling formatting
		if (keystates[SDLK_f]) g_player->interact();
		if (keystates[SDLK_RETURN]) toggleScreenFormat();
		if (keystates[SDLK_ESCAPE]) exitFullScreen();
}

void Game::Render()
{
    // Clear the screen
    SDL_FillRect(screen,NULL,0x000000);

	// Render everything
	g_camera->render();

	// Flip (update) the screen
	SDL_Flip(screen);
}

// Regulate the frame rate, and return the time (ms) since the last call
int Game::RegulateFrameRate()
{
	// Regulate FrameRate
	int ticks				= m_FPSTimer.get_ticks();
	int gap_between_frames	= 1000 / FRAME_RATE;

	if(ticks < gap_between_frames)
    {
        //Sleep the remaining frame time
        SDL_Delay(gap_between_frames - ticks);
		return gap_between_frames;
    }
	
	return 1000/ticks;
}

void Game::Poll()
{
	// Respond to events
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			running = false;
		}
	}
}