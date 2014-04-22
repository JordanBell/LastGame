#include "Entity.h"
#include "EntityContainer.h"
#include "Environment.h"
#include "Player.h"

void Entity::render(void) 
{ 
	if (this == g_player) isInSight = true;
	else
	{
		XY distFromPlayer = XY(g_player->x - getBlittingX(),
							   g_player->y - getBlittingY());
		int manDist = sqrt( distFromPlayer.x * distFromPlayer.x + distFromPlayer.y * distFromPlayer.y) / TILE_SIZE;

		isInSight = (manDist <= SIGHT_DISTANCE);
	}

	if (IsOnScreen()) 
	{
		if (LIMIT_RENDER_BY_SIGHT) { 
			if (isInSight) blit(); 
		}
		else blit();
	}
}

void Entity::move(int _x, int _y)
{
	x -= _x;
	y -= _y;
}

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
	return GetGridPosition(x, y); 
}

XY* Entity::GetGridPosition(float _x, float _y)
{
	XY* r_gridPosition = new XY(0, 0);

	int xDiff = (_x - g_environment->x) - TILE_SIZE/2;
	int yDiff = (_y - g_environment->y) - TILE_SIZE/2;
	// Note: TILE_SIZE/2 is added so that the rounding rounds to the nearest number, not just towards 0. Thus, this prevents incorrectly jumping to an adjacent square.

	// Round down to the nearest coordinate in terms of TILE_SIZE
	r_gridPosition->x = (xDiff / TILE_SIZE) + 1;
	r_gridPosition->y = (yDiff / TILE_SIZE) + 1;

	return r_gridPosition; 
}