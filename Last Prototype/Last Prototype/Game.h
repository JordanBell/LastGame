#ifndef game_h
#define game_h

#include <list>
#include "KeyCode.h"
#include "Entity.h"
#include "Player.h"
#include "Environment.h"
#include "Timer.h"
#include "Config.h"
class Game
{	
public:
	Game();
	~Game(void);
	void run();
    void addEntity(Entity* entity);
	void addABunchOfCoins();
	void MoveEverything(int x, int y);

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