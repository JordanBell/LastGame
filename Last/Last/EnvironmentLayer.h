#pragma once
#include "toolkit.h"
#include "EntityContainer.h"
#include "Config.h" // grid[][] size
#include <list>
using namespace std;

class Environment; // In order to make it a Friend, must be declared

class EnvironmentLayer : public EntityContainer
{
	friend class Environment; // Only the Environment class can access its layers

	EnvironmentLayer(bool staticImage = false);

	// When adding a child, add it to the array of tiles as well
	void AddChild(Entity* child);

	// Remove all tiles at a position
	void Erase(const Coordinates& gridPos);

	// 2D array of tiles in this layer
	list<Entity*> grid[WORLD_WIDTH][WORLD_HEIGHT]; 

	// Get the tile at a particular position
	list<Entity*>& GetEntitiesAt(Dimensions gridPosition);
};