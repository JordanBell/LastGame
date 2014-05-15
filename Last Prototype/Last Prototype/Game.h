#ifndef game_h
#define game_h

#include <list>
#include "KeyCode.h"
#include "Entity.h"
//#include "Player.h"
//#include "Environment.h"
#include "Timer.h"
#include "Config.h"
#include "Camera.h"
class Game
{	
public:
	Game();
	~Game(void);
<<<<<<< HEAD
	
	// Run the game, stick it in the game loop
	void run();
=======
	void run();
    void addEntity(Entity* entity);
	void addABunchOfCoins();
	void MoveEverything(int x, int y);
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete

private:
	//
	/// Fields
	//
	KeyCode keys;
	Timer m_FPSTimer;
	int delta; // The time since the last frame

<<<<<<< HEAD
	Timer m_FPSTimer; // The timer that keeps track of the time since the last update

	std::list<Entity*> m_Entities; // A list of entities used to call their render and update functions during the game loop
=======
	//Entities
	Player *player;
	Environment *environment;
	std::list<Entity*> m_Entities;
	bool running;
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete

	//
	/// Functions
	//
	void init();

	void Update();
		void HandleKeys();
		void CheckCollisions();
	void Render();
	void Poll();

	int RegulateFrameRate();
};

extern Game* g_game;

#endif