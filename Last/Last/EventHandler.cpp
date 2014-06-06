#include "EventHandler.h"
#include "ToolKit.h"
#include "GameStateManager.h"

EventHandler::EventHandler(void) 
{
	// Add this handler to a global list of handlers, which are passed event references
	g_manager->AddHandler(this);
}

EventHandler::~EventHandler(void) 
{
	// Remove this handler from the global list
	g_manager->RemoveHandler(this);
}
