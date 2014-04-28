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

XY Entity::GetGridPosition(XY _pos)
{
	XY r_gridPosition = _pos;

	// Round to the nearest multiple of TILE_SIZE
	r_gridPosition /= (float)TILE_SIZE;
	r_gridPosition.RoundToNearest();

	return r_gridPosition;
}

bool Entity::IsInSight(void)
{
	if (this == g_player) return true;
	else
	{
		XY distsFromPlayer = g_player->pos - getBlittingPos();
		int manDist = distsFromPlayer.manhatten() / TILE_SIZE;

		// Return whether this is within sight distance of the player
		return (manDist <= SIGHT_DISTANCE);
	}
}

bool Entity::IsOnScreen(void)
{
	XY blittingPos = getBlittingPos();
	XY dimensions(skin.h, skin.w);

	Directions<float>entityEdges(blittingPos.y - skin.h,
								 blittingPos.y + skin.h,
								 blittingPos.x - skin.w,
								 blittingPos.x + skin.w);

	// Return whether or not any of the edges peek over the screen
	return ((entityEdges.top	< screen->h) ||
			(entityEdges.left	< screen->w) ||
			(entityEdges.bottom > 0)		 ||
			(entityEdges.right	> 0));
}

bool Entity::ShouldRenderImage(void)
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