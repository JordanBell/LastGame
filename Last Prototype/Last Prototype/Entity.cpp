#include "Entity.h"
#include "EntityContainer.h"
#include "Environment.h"
#include "Player.h"

<<<<<<< HEAD
void Entity::e_render(void)
{ 
	if (ShouldRenderImage()) render();
}

void Entity::blit()
=======
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
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
{
	x -= _x;
	y -= _y;
}

<<<<<<< HEAD
XY Entity::getBlittingPos(void) const
=======
float Entity::getBlittingX(void) 
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
{
	if (parent == NULL) return x;
	else
	{
		// Add the parent's blitting x to this one
		return x + parent->getBlittingX();
	}
}

<<<<<<< HEAD
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
=======
float Entity::getBlittingY(void) 
{
	if (parent == NULL) return y;
	else
	{
		// Add the parent's blitting x to this one
		return y + parent->getBlittingY();
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
	}
	
	return true;
}

<<<<<<< HEAD
bool Entity::IsOnScreen(void) const
{
	const XY blittingPos = getBlittingPos();
	const XY dimensions(skin.h, skin.w);

	const Directions<float>entityEdges(blittingPos.y,
									   blittingPos.y + skin.h,
									   blittingPos.x,
									   blittingPos.x + skin.w);

	// Return whether or not any of the edges peek over the screen
	return ((entityEdges.top	< screen->h) &&
			(entityEdges.left	< screen->w) &&
			(entityEdges.bottom > 0)		 &&
			(entityEdges.right	> 0));
}

bool Entity::ShouldRenderImage(void) const
=======
XY* Entity::GetGridPosition()
{
	return GetGridPosition(x, y); 
}

XY* Entity::GetGridPosition(float _x, float _y)
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
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