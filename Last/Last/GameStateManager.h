#pragma once
#include "Tools.h"
#include "TitleScreenState.h"
#include "Game.h"
#include "Timer.h"
#include <list>

class GameState;
class EventHandler;

class GameStateManager
{
public:
	GameStateManager(void);
	~GameStateManager(void) { m_currentState->OnEnd(); }

	void Run(void);
	void Quit(void) { m_running = false; }

	// Choose a state to set via a given GameStateID
	void SwitchToState(GameStateID gsid);

	// Event Handler Functions
	void AddHandler(EventHandler* handler) { m_eventHandlers.push_back(handler); }
	void RemoveHandler(EventHandler* handler) { m_eventHandlers.remove(handler); }

private:
	std::list<EventHandler*> m_eventHandlers; // All of the handlers who are passed the events
	bool m_running; // The universal boolean for whether or not the program is running
	int delta; // The time since the last frame
	Timer m_FPSTimer; // The timer that keeps track of the time since the last update
	GameStateID startStateID;

	GameState* m_currentState; // Pointer to the current game state
	TitleScreenState* m_titleScreen; // The title screen game state
	Game* m_game; // The Main Game game state
	
	void Initialise(void);

	// Poll and pass events to the current state
	void HandleEvents(void);
	
	// Set the state, based on a state
	void SetState(GameState* state);

	// Regulate the framerate, and return the time since the last call.
	int RegulateFrameRate(void);
};

extern GameStateManager* g_manager;