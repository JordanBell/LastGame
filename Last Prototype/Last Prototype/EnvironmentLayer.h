#pragma once

#include "EntityContainer.h"
#include "GridTiles.h"
#include "Config.h"
#include "Tools.h"
#include "Player.h"

using namespace std;

class EnvironmentLayer : public EntityContainer
{
	friend class Environment; // Only the Environment class can access its layers

	list<GridTile<Entity>*> tiles[WORLD_WIDTH][WORLD_HEIGHT]; // 2D array of tiles in this layer

	EnvironmentLayer();

	// When adding a child, add it to the array of tiles as well
	void addChild(GridTile<Entity>* child);

	// Get the tile at a particular position
	list<GridTile<Entity>*>& GetTilesAt(XY gridPosition);
};