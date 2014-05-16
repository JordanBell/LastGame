#ifndef environment_h
#define environment_h

#include "EntityContainer.h"
#include "GridTiles.h"
#include "Config.h"
#include "Tools.h"
#include "Player.h"
#include "EnvironmentLayer.h"

/*
The environment is the EntityContainer that holds all of the tiles and 
entities that make up the world around the player. This essentially 
holds all of the entities that aren't either the player, or some sort of HUD.
*/
class Environment : public EntityContainer
{
	EnvironmentLayer topLayer;
	EnvironmentLayer bottomLayer;

public:
	Environment(float x, float y);

	void RenderTop(void) { topLayer.e_render(); }
	void RenderBottom(void) { bottomLayer.e_render(); }
	list<GridTile<Entity>*>& GetTilesAt(const XY& position, const bool top = false);
	void AddTileToTop(GridTile<Entity>* tile) { topLayer.addChild(tile); }
	void AddTileToBottom(GridTile<Entity>* tile) { bottomLayer.addChild(tile); }
};

extern Environment* g_environment;

#endif