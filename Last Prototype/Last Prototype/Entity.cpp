#include "Tools.h"
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

//XY* Entity::GetGridPosition()
//{
//	XY* r_gridPosition = new XY(0, 0);
//
//	int xDiff = x - g_environment->x;
//	int yDiff = y - g_environment->y;
//
//	// Round down to the nearest coordinate in terms of TILE_SIZE
//	r_gridPosition->x = xDiff / TILE_SIZE;
//	r_gridPosition->y = yDiff / TILE_SIZE;
//
//	return r_gridPosition; 
//}

int Entity::GetGridPosition()
{
	return 0;
}