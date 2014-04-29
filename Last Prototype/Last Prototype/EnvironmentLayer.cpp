#include "EnvironmentLayer.h"

EnvironmentLayer::EnvironmentLayer() : EntityContainer(0, 0) 
{
	for (int i = 0; i < WORLD_WIDTH; i++)
		for (int j = 0; j < WORLD_HEIGHT; j++)
			tiles[i][j] = NULL;
}
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