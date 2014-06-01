#pragma once
#include "SDL.h"

class GameStateManager;

/*
Game states managed and coordinated by the GameStateManager. 
Functions prefixed with "On-" are called by the GameStateManager.
*/
class GameState
{
	friend class GameStateManager;

protected:
	GameState(void) {}
	virtual ~GameState(void) {}
	
	// When starting up
	virtual void OnStart(void) = 0;
	virtual void OnEnd(void) = 0;

	// Update the entities
	virtual void OnUpdate(const int delta) = 0;

	// This GameState's response to a kind of event
	virtual void OnEvent(SDL_Event& event) {}

	// Respond to the given keystates array
	virtual void OnKeys(const Uint8* keystates) {}

	// GameState rendering
	virtual void Render(void) = 0;

private:
	// Clear, call Render, Update Renderer.
	void OnRender(void);
};

