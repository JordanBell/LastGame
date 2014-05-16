#include "Environment.h"
#include "Resources.h"
#include "HouseGenerator.h"
#include "Game.h"

Environment* g_environment = NULL;

Environment::Environment(float x, float y) : EntityContainer(x, y), topLayer(EnvironmentLayer()), bottomLayer(EnvironmentLayer())
{ 
	addChild(&topLayer);
	addChild(&bottomLayer);
}

list<GridTile<Entity>*>& Environment::GetTilesAt(const XY& position, const bool top)
{
	return top ? 
		   topLayer.GetTilesAt(position) : 
		   bottomLayer.GetTilesAt(position);
}