#pragma once
#include "Tools.h"
#include "Game.h"
#include "Timer.h"

class GameState;

class GameStateManager
{
public:
	GameStateManager(void);
	~GameStateManager(void) { m_currentState->OnEnd(); }

	void Run(void);
	void SetState(GameState& state);
	void Quit(void) { m_running = false; }

private:
	bool m_running; // The universal boolean for whether or not the program is running
	int delta; // The time since the last frame
	Timer m_FPSTimer; // The timer that keeps track of the time since the last update
	GameStateID startStateID;

	GameState* m_currentState; // Pointer to the current game state
	Game m_game; // The Main Game game state

	// Poll and pass events to the current state
	void HandleEvents(void);

	// Choose a state to set via a given GameStateID
	void SwitchToState(GameStateID gsid);

	// Regulate the framerate, and return the time since the last call.
	int RegulateFrameRate(void);
};

extern GameStateManager* g_manager;