#pragma once
#include "Timer.h"

#include "Tiles.h"
#include "TestEntity.h"

class Game
{	
public:
	Game();
	// Delete all entities.
	~Game(void);
	
	// Run the game, stick it in the game loop
	void Run();

private:
	int delta; // The time since the last frame
	bool running; // Whether or not the program is running - controls the game loop.
	Timer m_FPSTimer; // The timer that keeps track of the time since the last update
	
	TestEntity te1;
	TestEntity te2;
	TestEntity te3;
	TestEntity teMain;
	GrassTile testTile1;
	GrassTile testTile2;
	GrassTile testTile3;


	// Initialise all of the objects in the game.
	void init();

	// Update the entities
	void Update();
		void HandleKeys();
	// Render the entities
	void Render();
	// Check events with SDL
	void Poll();
	
	// Regulate the framerate, and return the delta time.
	int RegulateFrameRate();
};

extern Game* g_game;