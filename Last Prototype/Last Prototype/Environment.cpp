#include "Environment.h"
#include "Resources.h"
#include "HouseGenerator.h"
#include "Game.h"

Environment* g_environment = NULL;

void Environment::centerOn(Player* player)
{
	// Check to see where this would center to
	XY distFromCenter = player->pos - SCREEN_CENTER;
	XY suggestedPos = pos - distFromCenter;

	// Only center it if those coordinates are within the edges (Make x and y centering independant)
	Directions<bool> xBools = GetEdgeBools(suggestedPos.x, 0);
	Directions<bool> yBools = GetEdgeBools(0, suggestedPos.y);

	bool centerX = (!xBools.left && !xBools.right);
	bool centerY = (!yBools.top && !yBools.bottom);

	// Center the axis
	if (centerX) g_game->MoveEverything(-distFromCenter.x, 0);
	if (centerY) g_game->MoveEverything(0, -distFromCenter.y);

	// Snap everything real nice.
	player->SnapPosition();
}

Directions<bool> Environment::GetEdgeBools(int _x, int _y)
{
	Directions<bool> r_directions = Directions<bool>(
		(int)_y >= 0,
		(int)_y <= SCREEN_HEIGHT - WORLD_HEIGHT * TILE_SIZE,
		(int)_x >= 0,
		(int)_x <= SCREEN_WIDTH  - WORLD_WIDTH * TILE_SIZE);

	return r_directions;
}

GridTile* Environment::getTileAt(XY gridPosition)
{
	return tiles[(int)gridPosition.x][(int)gridPosition.y];
}