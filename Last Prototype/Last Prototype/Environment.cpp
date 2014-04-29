#include "Environment.h"
#include "Resources.h"
#include "HouseGenerator.h"
#include "Game.h"

Environment* g_environment = NULL;

Environment::Environment(float x, float y) : EntityContainer(x, y)
{ 
	topLayer = EnvironmentLayer(); 
	bottomLayer = EnvironmentLayer(); 

	addChild(&topLayer);
	addChild(&bottomLayer);
}

GridTile* Environment::GetTileAt(XY position, bool top)
{
	return top ? 
		   topLayer.GetTileAt(position) : 
		   bottomLayer.GetTileAt(position);
}