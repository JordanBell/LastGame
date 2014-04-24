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
	Environment(float x, float y) : EntityContainer(x, y) {}

	// Try to center the environment on the player, if doing so would not overstep the edges
	void centerOn(Player* player);

	// Get the tile at a particular position
	GridTile* getTileAt(XY gridPosition);

	// Return, for each direction, whether or not this position exposes the unrendered edge of the world
	Directions<bool> Environment::GetEdgeBools() { return GetEdgeBools((int)x, (int)y); }

	// Return, for each direction, whether or not a given position will expose the unrendered edge of the world
	Directions<bool> GetEdgeBools(int _x, int _y);

private:
	int width, height; //The total size of the world
	GridTile* tiles[WORLD_WIDTH][WORLD_HEIGHT]; // 2D array of tiles in the world
};

extern Environment* g_environment;

#endif