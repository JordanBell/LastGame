#include "Environment.h"
#include "Resources.h"
#include "HouseGenerator.h"
#include "Game.h"

Environment* g_environment = NULL;

GridTile* Environment::getTileAt(XY gridPosition)
{
	return tiles[(int)gridPosition.x][(int)gridPosition.y];
}