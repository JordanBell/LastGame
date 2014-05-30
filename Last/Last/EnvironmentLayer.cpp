#include "EnvironmentLayer.h"
#include "Config.h"

EnvironmentLayer::EnvironmentLayer(bool staticImage) : EntityContainer(WORLD_DIMENSIONS * TILE_SIZE, Coordinates(0, 0), staticImage)
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

	// Check validity of position
	bool validX = ((childGridPos.x >= 0) || (childGridPos.x <= WORLD_WIDTH));
	bool validY = ((childGridPos.y >= 0) || (childGridPos.y <= WORLD_HEIGHT));
	if (!validX || !validY) 
		throw std::runtime_error("Invalid position on the grid.");

	list<Entity*>& entitiesAtThisPosition = GetEntitiesAt(childGridPos);
	entitiesAtThisPosition.push_back(child);

	// Add the child as usual
	EntityContainer::AddChild(child);
}

list<Entity*>& EnvironmentLayer::GetEntitiesAt(Coordinates gridPosition)
{
	return grid[(int)gridPosition.x][(int)gridPosition.y];
}