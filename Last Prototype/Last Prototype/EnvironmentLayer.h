#pragma once

#include "EntityContainer.h"
#include "GridTiles.h"
#include "Config.h"
#include "Tools.h"
#include "Player.h"

class EnvironmentLayer : public EntityContainer
{
	friend class Environment; // Only the Environment class can access its layers

	GridTile* tiles[WORLD_WIDTH][WORLD_HEIGHT]; // 2D array of tiles in this layer

	EnvironmentLayer();

	// When adding a child, add it to the array of tiles as well
	void addChild(GridTile* child);

	// Get the tile at a particular position
	GridTile* GetTileAt(XY gridPosition);
};