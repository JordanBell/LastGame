#include "Game.h"
#include "SDL.h"
#include <time.h>
<<<<<<< HEAD
#include "WorldBuilder.h"
#include "Player.h"
#include "Environment.h"
=======
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete

Game* g_game = NULL;

Game::Game() : running(true)
{
	delta = 0;
	srand(time(NULL));
}

<<<<<<< HEAD
Game::~Game() { delete g_camera; }

void Game::init()
{
	// Initiailise the Environment and Player
	g_environment = new Environment(0, 0);
	WorldBuilder::build();
	g_player = new Player((int)(WORLD_WIDTH/2), (int)(WORLD_HEIGHT/2));
	// Add everything to the AllContainer
	g_camera = new Camera();
=======
void Game::init()
{
	// Initialise all ENTITIES
	g_environment = new Environment(0, 0);
	environment = g_environment;
	environment->BuildMap();

	// Place the player in the center of the world
	g_player = new Player((int)(WORLD_WIDTH/2), (int)(WORLD_HEIGHT/2));
	player = g_player;
	
	m_Entities.push_back(environment);
	m_Entities.push_back(player);

	// Center everything on the player
	environment->centerOn(player);

	// Set up the key responses
	keys = KeyCode(player);
}

Game::~Game(void)
{
	// Delete all entities
	for (Entity* e : m_Entities) { delete e; }
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
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

void Game::Update()
{
	HandleKeys();
	
<<<<<<< HEAD
	// Update the entities
	g_camera->update(delta);
=======
	for (Entity* e : m_Entities) { e->update(delta); }
}

void Game::MoveEverything(int x, int y)
{
	// Move all entities by the specified x and y amounts
	for (Entity* e : m_Entities) 
	{ 
		e->x += x; 
		e->y += y; 
	}

>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
}

void Game::HandleKeys()
{
	//Get the keystates
	Uint8 *keystates = SDL_GetKeyState(NULL);
	
<<<<<<< HEAD
		//WASD moves the player
		if (keystates[SDLK_w])	g_player->walk(UP);
		if (keystates[SDLK_s])	g_player->walk(DOWN);
		if (keystates[SDLK_a])	g_player->walk(LEFT);
		if (keystates[SDLK_d])	g_player->walk(RIGHT);

		// Toggling formatting
		if (keystates[SDLK_f]) g_player->interact();
		if (keystates[SDLK_RETURN]) toggleScreenFormat();
		if (keystates[SDLK_ESCAPE]) running = false;
=======
	//If WASD, move player
	if (keystates[SDLK_w] || keystates[SDLK_s] || keystates[SDLK_a] || keystates[SDLK_d])
	{
		if (keystates[SDLK_a])	keys.left();
		if (keystates[SDLK_d])	keys.right();
		if (keystates[SDLK_w])	keys.up();
		if (keystates[SDLK_s])	keys.down();
	}

	// Screen Formatting
	if (keystates[SDLK_f]) toggleScreenFormat();
	if (keystates[SDLK_ESCAPE]) exitFullScreen();
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
}

void Game::Render()
{
    // Clear the screen
    SDL_FillRect(screen,NULL,0x000000);

<<<<<<< HEAD
	// Render everything
	g_camera->render();
=======
	// Render all of the entities
	for (Entity* e : m_Entities) { e->render(); }
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete

	// Flip (update) the screen
	SDL_Flip(screen);
}

<<<<<<< HEAD
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

=======
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
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

void Game::addEntity(Entity* entity)
{
    m_Entities.push_back(entity);
}