#pragma once
#include "SDL.h"

class EventHandler
{
public:
	// Remove this handler from the global list
	~EventHandler(void);

	// When passed an event...
	virtual void OnEvent(SDL_Event& event) = 0;

protected:
	// Add this handler to a global list of handlers, which are passed event references
	EventHandler(void);
};

