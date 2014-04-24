#include "Entity.h"
#include "EntityContainer.h"
#include "Environment.h"
#include "Player.h"

void Entity::move(XY displacement)
{
	pos += displacement;
}

void Entity::render(void) 
{ 
	if (this == g_player) isInSight = true;
	else
	{
		XY distsFromPlayer = g_player->pos - getBlittingPos();
		int manDist = distsFromPlayer.manhatten() / TILE_SIZE;

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

void Entity::blit()
{
	XY blitPos = getBlittingPos();
	apply_surface(blitPos, sprite_sheet, screen, &skin);
}

XY Entity::getBlittingPos(void) 
{
	if (parent == NULL) return pos;
	else
	{
		// Add the parent's blitting x to this one
		return pos + parent->getBlittingPos();
	}
}

float Entity::getBlittingX(void) 
{
	printf("getBlittingX() is being used");
	if (parent == NULL) return *x;
	else
	{
		// Add the parent's blitting x to this one
		return *x + parent->getBlittingX();
	}
}

float Entity::getBlittingY(void)
{
	printf("getBlittingX() is being used");
	if (parent == NULL) return *y;
	else
	{
		// Add the parent's blitting x to this one
		return *y + parent->getBlittingY();
	}
}

XY Entity::GetGridPosition(XY _pos)
{
	XY diff = (_pos - g_environment->pos) - TILE_SIZE/2;
	// Note: TILE_SIZE/2 is added so that the rounding rounds to the nearest number, not just towards 0. Thus, this prevents incorrectly jumping to an adjacent square.
	// Note: TILE_SIZE/2 is subtracted so that the rounding rounds to the nearest number, not just towards 0. Thus, this prevents incorrectly jumping to an adjacent square.

	// Round down to the nearest coordinate in terms of TILE_SIZE
	XY r_gridPosition = diff/TILE_SIZE + 1; // Add 1 to compensate for consistent deviation

	return r_gridPosition; 
}

bool Entity::IsOnScreen(void)
{
	return ((getBlittingX() <= screen->w) && (getBlittingY() <= screen->h));
}