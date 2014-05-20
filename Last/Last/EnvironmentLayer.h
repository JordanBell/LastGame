#pragma once
#include "toolkit.h"
#include "EntityContainer.h"
#include "Config.h" // grid[][] size
#include <list>
using namespace std;

class Environment; // In order to make it a Friend

class EnvironmentLayer : public EntityContainer
{
	friend class Environment; // Only the Environment class can access its layers

	list<Entity*> grid[WORLD_WIDTH][WORLD_HEIGHT]; // 2D array of tiles in this layer

	EnvironmentLayer(bool staticImage = false);

	// When adding a child, add it to the array of tiles as well
	void AddChild(Entity* child);

	// Get the tile at a particular position
	list<Entity*>& GetEntitiesAt(Dimensions gridPosition);
};