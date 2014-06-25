#include "GameStateManager.h"
#include "EventHandler.h"
#include "ToolKit.h"
#include "Game.h"
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
			int size = m_eventHandlers.size();
			printf("EventHandler count: %d\n", size);

			list<EventHandler*> handlerCopyList = m_eventHandlers;
			for (EventHandler* handler : handlerCopyList)
				handler->OnEvent(event);

			/*for (EventHandler* handler : m_eventHandlers)
				handler->OnEvent(event);*/
		}
	}
}


void GameStateManager::SwitchToState(GameStateID gsid)
{
	switch (gsid)
	{
	case GSID_TITLE: SetState(m_titleScreen); break;
	case GSID_MAIN:  SetState(m_game);		  break;
	default:		throw std::runtime_error("Cannot recognise the given GameStateID");
	}
}

void GameStateManager::SetState(GameState* state)
{
	// Old state's End call
	if (m_currentState) 
		m_currentState->OnEnd();

	// Set the new state
	m_currentState = state;

	// New state's Start call
	m_currentState->OnStart();
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
