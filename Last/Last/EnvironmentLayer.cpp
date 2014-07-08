#include "EnvironmentLayer.h"
#include "Config.h"
#include <algorithm>

EnvironmentLayer::EnvironmentLayer(bool staticImage) 
	: EntityContainer(WORLD_DIMENSIONS * TILE_SIZE, Coordinates(0, 0), staticImage)
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

	// Erase the tiles at this position if Exclusive Tiles is set to true - only this new child will be at that position
	if (EXCLUSIVE_TILES) Erase(childGridPos);

	list<Entity*>& entitiesAtThisPosition = GetEntitiesAt(childGridPos);
	entitiesAtThisPosition.push_back(child);

	// Add the child as usual
	EntityContainer::AddChild(child);
}

void EnvironmentLayer::Erase(const Coordinates& gridPos)
{
	// Check validity of position
	bool validX = ((gridPos.x >= 0) || (gridPos.x <= WORLD_WIDTH));
	bool validY = ((gridPos.y >= 0) || (gridPos.y <= WORLD_HEIGHT));
	if (!validX || !validY) 
		throw std::runtime_error("Invalid position on the grid.");

	// Clear the Entity list at this position
	auto localList = grid[(int)gridPos.x][(int)gridPos.y]; // Save the list locally, so that it can be looped through after deletion to find the children there.
	if (!localList.empty())
	{
		grid[(int)gridPos.x][(int)gridPos.y].clear();

		// Delete the children at that position. Terribly inefficient method, shouldn't be a problem as this is done to small localList objects
		for (auto& deletionChild : localList)
		{
			// Find the matching unique_ptr
			auto i = children.begin();
			auto e = children.end();
			while (i != e)
			{
				if (deletionChild == i->get()) 
					i = children.erase(i);
				else
					++i;
			}
		}
	} // Only calculate all of that if the position is non-empty

	// If this image is static, replace those pixels with empty alpha
	if (GetImage().IsStatic())
	{
		SDL_Rect rect = { gridPos.x*TILE_SIZE, gridPos.y*TILE_SIZE, TILE_SIZE, TILE_SIZE};
		GetImage().Clear(&rect);
	}

}

list<Entity*>& EnvironmentLayer::GetEntitiesAt(Coordinates gridPosition)
{
	return grid[(int)gridPosition.x][(int)gridPosition.y];
}