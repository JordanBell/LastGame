#include "EnvironmentLayer.h"

EnvironmentLayer::EnvironmentLayer() : EntityContainer(0, 0) 
{
	for (int i = 0; i < WORLD_WIDTH; i++)
		for (int j = 0; j < WORLD_HEIGHT; j++)
			tiles[i][j] = std::list<GridTile<Entity>*>();
}
void EnvironmentLayer::addChild(GridTile<Entity>* child)
{
	// Add it to the tiles array
	XY childGridPos = child->pos / TILE_SIZE;
	list<GridTile<Entity>*>& tilesAtThisPosition = GetTilesAt(childGridPos);
	tilesAtThisPosition.push_back(child);

	// Add the child as usual
	EntityContainer::addChild(child);
}

list<GridTile<Entity>*>& EnvironmentLayer::GetTilesAt(XY gridPosition)
{
	return tiles[(int)gridPosition.x][(int)gridPosition.y];
}