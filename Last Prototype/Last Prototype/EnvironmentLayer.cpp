#include "EnvironmentLayer.h"

void EnvironmentLayer::addChild(GridTile* child)
{
	// Add it to the tiles array
	XY i = child->pos / TILE_SIZE;
	tiles[(int)i.x][(int)i.y] = child;

	// Add the child as usual
	EntityContainer::addChild(child);
}

GridTile* EnvironmentLayer::GetTileAt(XY gridPosition)
{
	return tiles[(int)gridPosition.x][(int)gridPosition.y];
}