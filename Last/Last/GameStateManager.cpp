#include "GameStateManager.h"
#include "EventHandler.h"
#include "ToolKit.h"
#include "Game.h"
#include "KeyTools.h"
#include <time.h>

GameStateManager* g_manager = nullptr;

GameStateManager::GameStateManager(void) 
	: m_eventHandlers(), delta(0), m_running(true), startStateID(GSID_TITLE), 
	  m_currentState(nullptr), m_titleScreen(nullptr), m_game(nullptr)
{
	// Initialise time
	srand(time(nullptr));
}

void GameStateManager::Initialise(void)
{
	m_titleScreen = new TitleScreenState();
	m_game = new Game();

	// Initialise with start state
	SwitchToState(startStateID);
	
	// Start the timer, for frame rate functions
	m_FPSTimer.start();
}


void GameStateManager::Run(void)
{
	Initialise();

	while (m_running)
	{
		// If a new state is set to begin, set it now
		if (m_preparedState)
			InitialisePreparedState();

		// Update static key states
		KeyTools::UpdateStates();
		// State's key press responses
		m_currentState->OnKeys(SDL_GetKeyboardState(nullptr));
		// Update State
		m_currentState->OnUpdate(delta);
		// Render State
		m_currentState->OnRender();
		
		HandleEvents();
		delta = RegulateFrameRate();
	}

	delete this;
}


void GameStateManager::HandleEvents(void)
{
	// Respond to events
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) {
			m_running = false; // Quit
		}
		else 
		{
			for (EventHandler* handler : m_eventHandlers)
				handler->OnEvent(event);
		}
	}
}


void GameStateManager::SwitchToState(GameStateID gsid)
{
	switch (gsid)
	{
	case GSID_TITLE: PrepareState(m_titleScreen); break;
	case GSID_MAIN:  PrepareState(m_game);		  break;
	default:		throw std::runtime_error("Cannot recognise the given GameStateID");
	}
}

void GameStateManager::InitialisePreparedState(void)
{
	// Old state's End call
	if (m_currentState) 
		m_currentState->OnEnd();

	// Clear the list of event handlers
	m_eventHandlers.clear();

	// Set the new state
	m_currentState = m_preparedState;

	// New state's Start call
	m_currentState->OnStart();

	// Reset the prepared state to null
	m_preparedState = nullptr;
}

void GameStateManager::PrepareState(GameState* state)
{
	/*
	If the state is changed right now, as this function is called, it will interrupt the 
	game loop and confuse the values assumed within it (ie the list of event handlers, 
	if this was evoked in response). As the temporary pointer is non-null, the conditional
	in the game loop to change the state is executed.
	*/

	m_preparedState = state;
}


int GameStateManager::RegulateFrameRate(void)
{
	// Regulate FrameRate
	int ticks			= m_FPSTimer.get_ticks();
	int idealTimeGap	= 1000 / FRAME_RATE;

	// If the time since last time is less than ideal
	if (ticks < idealTimeGap)
    {
        // Slow things down a bit
        SDL_Delay(idealTimeGap - ticks);

		// Return that time
		return idealTimeGap;
    }
	
	// Else, return the observed (slower) time since last call.
	return 1000/ticks;
}
