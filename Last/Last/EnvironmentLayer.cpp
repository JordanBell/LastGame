#include "EnvironmentLayer.h"
#include "Config.h"

EnvironmentLayer::EnvironmentLayer(bool staticImage) : EntityContainer(WORLD_DIMENSIONS * TILE_SIZE, Coordinates(), staticImage) 
{
	for (int i = 0; i < WORLD_WIDTH; i++)
		for (int j = 0; j < WORLD_HEIGHT; j++)
			grid[i][j] = std::list<Entity*>();
}
void EnvironmentLayer::AddChild(Entity* child)
{
	if ((*child)[GRID_INDEPENDENT]) throw ModuleMisuseException("Cannot add a grid independent Entity to the EnvironmentLayer grid.");

	// Add it to the Entity array
	Coordinates childGridPos = child->pos / TILE_SIZE;
	list<Entity*>& entitiesAtThisPosition = GetEntitiesAt(childGridPos);
	entitiesAtThisPosition.push_back(child);

	// Add the child as usual
	EntityContainer::AddChild(child);
}

list<Entity*>& EnvironmentLayer::GetEntitiesAt(Coordinates gridPosition)
{
	return grid[(int)gridPosition.x][(int)gridPosition.y];
}