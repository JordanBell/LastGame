#pragma once

#include "Game.h"
#include "Camera.h" // Initialising g_camera
#include "Player.h" // Initialising g_player
#include "HUD_Layer.h" // UI HUD

Game* g_game = nullptr;

Game::~Game() 
{ 
	delete g_camera; 
	delete UI_HUD;
}

void Game::Init()
{
	// Initialise the UI
	UI_HUD = new HUD_Layer();
		UI_Fatigue = new UI_Status(g_fatigue, Coordinates(0, 0));
		UI_Loneliness = new UI_Status(g_loneliness, Coordinates(1, 0));
		UI_Insanity = new UI_Status(g_insanity, Coordinates(0, 1));
		UI_Fear = new UI_Status(g_fear, Coordinates(1, 1));
	UI_HUD->InitChildren(); // Add all of the above to the HUD Layer

	// Initiailise the Environment
	g_environment = new Environment();
	g_environment->Initialise();

	// Initialise the Player
	Coordinates worldCenter((WORLD_WIDTH/2), (WORLD_HEIGHT/2));
	g_player = new Player(worldCenter);
	g_environment->AddToMiddle(g_player); // Stick the player in the world.

	// Add everything to the Camera
	g_camera = new Camera();
	g_camera->InitChildren();
}

void Game::Run()
{	
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
	UI_HUD->Update(delta);
}

void Game::HandleKeys()
{
	//Get the keystates
	const Uint8* keystates = SDL_GetKeyboardState(nullptr);
	
		//WASD moves the player
		if (keystates[SDL_SCANCODE_W])	g_player->Walk(UP);
		if (keystates[SDL_SCANCODE_S])	g_player->Walk(DOWN);
		if (keystates[SDL_SCANCODE_A])	g_player->Walk(LEFT);
		if (keystates[SDL_SCANCODE_D])	g_player->Walk(RIGHT);

		// Other
		if (keystates[SDL_SCANCODE_F]) g_player->Interact();
		if (keystates[SDL_SCANCODE_RETURN]) ToggleFullscreen();
		if (keystates[SDL_SCANCODE_ESCAPE]) running = false;

		// Testing
		if (MANUAL_ZOOM)
		{
			// Up and Down to zoom in and out
			if (keystates[SDL_SCANCODE_UP]) if (!g_camera->ZoomToWidth(++widthCounter)) widthCounter--;
			if (keystates[SDL_SCANCODE_DOWN]) if (!g_camera->ZoomToWidth(--widthCounter)) widthCounter++;
		}
		else
		{
			// Up, Down, Left, Right move the player, as does WASD
			if (keystates[SDL_SCANCODE_UP]) g_player->Walk(UP);
			if (keystates[SDL_SCANCODE_DOWN]) g_player->Walk(DOWN);
			if (keystates[SDL_SCANCODE_LEFT]) g_player->Walk(LEFT);
			if (keystates[SDL_SCANCODE_RIGHT]) g_player->Walk(RIGHT);
		}
}

void Game::Render()
{
	//Clear screen
	ClearWindow();

	// Render camera (Everything on screen)
	g_camera->Render();
	// Render UI HUD
	//UI_HUD->Render();

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