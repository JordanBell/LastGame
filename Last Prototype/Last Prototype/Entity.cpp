#include "Entity.h"
#include "EntityContainer.h"
#include "Environment.h"
#include "Player.h"

void Entity::move(XY displacement)
{
	pos += displacement;
	//pos -= displacement;
}

void Entity::e_render(void) 
{ 
	if (ShouldRenderImage()) render();
}

void Entity::render(void) 
{ 
	blit();
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
	XY diff = (_pos - g_environment->pos) - TILE_SIZE/2;
	// Note: TILE_SIZE/2 is subtracted so that the rounding rounds to the nearest number, not just towards 0. Thus, this prevents incorrectly jumping to an adjacent square.

	// Round down to the nearest coordinate in terms of TILE_SIZE
	XY r_gridPosition = diff/TILE_SIZE + 1; // Add 1 to compensate for consistent deviation

	return r_gridPosition;
}

bool Entity::IsInSight(void)
{
	if (this == g_player) return true;
	else
	{
		XY distsFromPlayer = g_player->pos - getBlittingPos();
		int manDist = distsFromPlayer.manhatten() / TILE_SIZE;

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