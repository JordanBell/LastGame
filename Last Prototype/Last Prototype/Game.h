#ifndef game_h
#define game_h

#include <list>
#include "KeyCode.h"
#include "Entity.h"
#include "Player.h"
#include "Environment.h"
#include "Timer.h"

#define TILE_SIZE 32
#define FRAME_RATE 60
class Game
{	
public:
	Game();
	~Game(void);
	void run();
    void addEntity(Entity* entity);
	void addABunchOfCoins();

private:
	//
	/// Fields
	//
	KeyCode keys;
	Timer m_FPSTimer;
	int delta; // The time since the last frame

	//Entities
	Player *player;
	Environment *environment;
	std::list<Entity*> m_Entities;
	bool running;

	//
	/// Functions
	//
	void Update();
		void HandleKeys();
		void CheckCollisions();
	void Render();
	void Poll();

	int RegulateFrameRate();
};

extern Game* g_game;

#endif