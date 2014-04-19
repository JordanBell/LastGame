#include "Entity.h"
#include "EntityContainer.h"
#include "Environment.h"

float Entity::getBlittingX(void) 
{
	if (parent == NULL) return x;
	else
	{
		// Add the parent's blitting x to this one
		return x + parent->getBlittingX();
	}
}

float Entity::getBlittingY(void) 
{
	if (parent == NULL) return y;
	else
	{
		// Add the parent's blitting x to this one
		return y + parent->getBlittingY();
	}
}

XY* Entity::GetGridPosition()
{
	XY* r_gridPosition = new XY(0, 0);

	int xDiff = (x - g_environment->x) - TILE_SIZE/2;
	int yDiff = (y - g_environment->y) - TILE_SIZE/2;
	// Note: Add TILE_SIZE/2 so that the rounding rounds to the nearest number, not just towards 0. Thus, this prevents incorrectly jumping to an adjacent square.

	// Round down to the nearest coordinate in terms of TILE_SIZE
	r_gridPosition->x = (xDiff / TILE_SIZE) + 1;
	r_gridPosition->y = (yDiff / TILE_SIZE) + 1;

	return r_gridPosition; 
}