#ifndef game_h
#define game_h

#include <list>
#include "Entity.h"
//#include "Player.h"
//#include "Environment.h"
#include "Timer.h"
#include "Config.h"
#include "AllContainer.h"
class Game
{	
public:
	Game();
	// Delete all entities.
	~Game(void);



	// Run the game, stick it in the game loop
	void run();

	// Move all of the entities by a certain amount
	//void MoveEverything(XY displacement);

private:
	int delta; // The time since the last frame
	bool running; // Whether or not the program is running - controls the game loop.

	Timer m_FPSTimer; // The timer that keeps track of the time since the last update

	//Player* player; // The player in the game.
	//Environment* environment; // The EntityContainer containing the entire environment
	std::list<Entity*> m_Entities; // A list of entities used to call their render and update functions during the game loop



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

#endif