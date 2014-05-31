#ifndef environment_h
#define environment_h

#include "EnvironmentLayer.h"
#include "Tiles.h"

/*
The environment is the EntityContainer that separates the three layers in the world.
This allows for separate and ordered blitting, which creates a layering effect
*/
class Environment : public EntityContainer
{
	EnvironmentLayer topLayer;	  // Tall walls, ceilings, anying rendered above the player
	EnvironmentLayer middleLayer; // The player, items, other travellers, interactables
	EnvironmentLayer bottomLayer; // Floors, low walls, anything rendered below the player

public:
	Environment() : EntityContainer(WORLD_DIMENSIONS * TILE_SIZE), 
					topLayer(true), 
					middleLayer(false), 
					bottomLayer(true) {}

	// Add the layers as children to the Environment, along with any other initialisation required beyond the constructor.
	void Initialise(void);

	void AddToTop(Entity* child)	{ topLayer.AddChild(child); }
	void AddToMiddle(Entity* child)	{ middleLayer.AddChild(child); }
	void AddToBottom(Entity* child)	{ bottomLayer.AddChild(child); }

	// Get a list of pointers to all of the entities at a given position
	list<Entity*>& GetEntitiesAt(const Coordinates& position, const Layer layer = BOTTOM_LAYER);
};

extern Environment* g_environment;

#endif