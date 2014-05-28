#pragma once

#include "Game.h"
#include <time.h>	// Initialising timer
#include "Camera.h" // Initialising g_camera
#include "Player.h" // Initialising g_player
#include "WorldBuilder.h" // Building the world

Game* g_game = NULL;

Game::Game() : running(true)
{
	delta = 0;
	srand(time(NULL));
}

Game::~Game() { delete g_camera; }

void Game::init()
{
	// Initialise the Player
	Coordinates worldCenter((WORLD_WIDTH/2), (WORLD_HEIGHT/2));
	g_player = new Player(worldCenter);

	// Initiailise the Environment
	g_environment = new Environment();
	WorldBuilder::build();
	g_environment->AddToMiddle(g_player); // Add the player to the environment

	// Add everything to the Camera
	g_camera = new Camera();
	g_camera->InitChildren();
}

void Game::Run()
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
	g_camera->Update(delta);
}

void Game::HandleKeys()
{
	//Get the keystates
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	
		//WASD moves the player
		if (keystates[SDL_SCANCODE_W])	g_player->Walk(UP);
		if (keystates[SDL_SCANCODE_S])	g_player->Walk(DOWN);
		if (keystates[SDL_SCANCODE_A])	g_player->Walk(LEFT);
		if (keystates[SDL_SCANCODE_D])	g_player->Walk(RIGHT);

		// Toggling formatting
		if (keystates[SDL_SCANCODE_F]) g_player->Interact();
		if (keystates[SDL_SCANCODE_RETURN]) ToggleFullscreen();
		if (keystates[SDL_SCANCODE_ESCAPE]) running = false;
}

void Game::Render()
{
	//Clear screen
	ClearWindow();

	// Render camera (Everything on screen)
	g_camera->Render();

	// Update the screen
	UpdateWindow();
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