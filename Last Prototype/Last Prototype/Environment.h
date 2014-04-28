#ifndef environment_h
#define environment_h

#include "EntityContainer.h"
#include "GridTiles.h"
#include "Config.h"
#include "Tools.h"
#include "Player.h"

#define WORLD_BORDER ShinyBlockTile

/*
The environment is the EntityContainer that holds all of the tiles and 
entities that make up the world around the player. This essentially 
holds all of the entities that aren't either the player, or some sort of HUD.
*/
class Environment : public EntityContainer
{

public:
	GridTile* tiles[WORLD_WIDTH][WORLD_HEIGHT]; // 2D array of tiles in the world

	Environment(float x, float y) : EntityContainer(x, y) {}

	// Get the tile at a particular position
	GridTile* getTileAt(XY gridPosition);

private:
	int width, height; //The total size of the world
};

extern Environment* g_environment;

#endif