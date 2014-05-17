#include "Entity.h"
#include "EntityContainer.h"
#include "Environment.h"
#include "Player.h"

void Entity::e_render(void)
{ 
	if (ShouldRenderImage()) render();
}

void Entity::blit()
{
	XY blitPos = getBlittingPos();
	apply_surface(blitPos, sprite_sheet, &skin);
}

XY Entity::getAbsolutePos(void) const
{
	if (parent == NULL) return pos;
	else
	{
		// Add the parent's blitting x to this one
		return pos + parent->getAbsolutePos();
	}
}

XY Entity::GetGridPosition(const XY& _pos)
{
	XY r_gridPosition = _pos;

	// Round to the nearest multiple of TILE_SIZE
	r_gridPosition /= (float)TILE_SIZE;
	r_gridPosition.RoundToNearest();

	return r_gridPosition;
}

bool Entity::IsInSight(void) const
{
	if (this != g_player)
	{
		if (g_player != NULL)
		{
			XY distsFromPlayer = g_player->pos - getBlittingPos();
			int manDist = distsFromPlayer.manhatten() / TILE_SIZE;

			// Return whether this is within sight distance of the player
			return (manDist <= SIGHT_DISTANCE);
		}
	}
	
	return true;
}

bool Entity::IsOnScreen(void) const
{
	const XY blittingPos = getBlittingPos();
	const XY dimensions(skin.h, skin.w);

	const Directions<float>entityEdges(blittingPos.y,
									   blittingPos.y + skin.h,
									   blittingPos.x,
									   blittingPos.x + skin.w);

	// Return whether or not any of the edges peek over the screen
	return ((entityEdges.top	< g_windowSurface->h) &&
			(entityEdges.left	< g_windowSurface->w) &&
			(entityEdges.bottom > 0)		 &&
			(entityEdges.right	> 0));
}

bool Entity::ShouldRenderImage(void) const
{
	if (IsOnScreen()) 
	{
		if (LIMIT_RENDER_BY_SIGHT) { 
			if (IsInSight()) return true; 
		}
		else return true;
	}

	return false;
}