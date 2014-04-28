#include "AllContainer.h"
#include "Player.h"

AllContainer* g_all = NULL;

AllContainer::AllContainer(void) : EntityContainer(0, 0)
{
	addChild(g_environment);
	addChild(g_player);
}


AllContainer::~AllContainer(void)
{
	// Delete Player
	delete g_player;

	// Delete Environment
	delete g_environment;
}

bool AllContainer::MovingIntoEdges(void)
{
	// Do not move the camera if the map is at the edge - we don't want to show unrendered areas.
	Directions<bool> atEdge = GetEdgeBools();
		
	if ((atEdge.top	   && g_player->getDirection() == UP)	||
		(atEdge.bottom && g_player->getDirection() == DOWN) ||
		(atEdge.left   && g_player->getDirection() == LEFT) ||
		(atEdge.right  && g_player->getDirection() == RIGHT)) return true;
	else return false;
}

void AllContainer::update(int delta)
{ 
	// Call the usual Container update
	EntityContainer::update(delta);
	
	// Center the camera onto the player
	CenterOnPlayer(); 
}

void AllContainer::CenterOnPlayer()
{
	// Do not move the camera if the map is at the edge - we don't want to show unrendered areas.
	//if (!MovingIntoEdges())
	//{
		//// Check to see where this would center to
		//XY distFromCenter = g_player->getBlittingPos() - SCREEN_CENTER;

		//// Round that distance to a multiple of TILE_SIZE  // Why?
		///*distFromCenter /= TILE_SIZE;
		//distFromCenter.RoundToInt();
		//distFromCenter *= TILE_SIZE;*/

		//XY suggestedPos = g_environment->getBlittingPos() - distFromCenter;

		//// Only center it if those coordinates are within the edges (Make x and y centering independant)
		//Directions<bool> xBools = GetEdgeBools(XY(suggestedPos.x, 0));
		//Directions<bool> yBools = GetEdgeBools(XY(0, suggestedPos.y));

		//bool centerX = ;
		//bool centerY = (!yBools.top  && !yBools.bottom);

		//// Center the axis
		//if (centerX) pos.x -= distFromCenter.x;
		//if (centerY) pos.y -= distFromCenter.y;
	//}

	// Get the coordinates that the camera would move to to center on the player
	XY screenCenter = SCREEN_CENTER;
	XY suggestedPos = screenCenter - g_player->pos;

	// Check to see if that would reveal any edges
	Directions<bool> edgeBools = GetEdgeBools(suggestedPos);

	// Check the validity for each axis
	bool canCenterX = (!edgeBools.left && !edgeBools.right);
	bool canCenterY = (!edgeBools.top  && !edgeBools.bottom);
		
	// Center on the valid axes
	if (canCenterX) pos.x = suggestedPos.x;
	if (canCenterY) pos.y = suggestedPos.y;
}

Directions<bool> AllContainer::GetEdgeBools(XY _pos)
{
	_pos.RoundToInt();

	Directions<bool> r_directions = Directions<bool>(
		_pos.y >= 0,
		_pos.y <= SCREEN_HEIGHT - WORLD_HEIGHT * TILE_SIZE,
		_pos.x >= 0,
		_pos.x <= SCREEN_WIDTH  - WORLD_WIDTH * TILE_SIZE);

	return r_directions;
}