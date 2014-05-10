#pragma once
#include "Camera.h"
#include "Player.h"

Camera* g_camera = NULL;

Camera::Camera(void) : EntityContainer(0, 0)
{
	addChild(g_environment);
	addChild(g_player);
}

Camera::~Camera(void)
{
	// Delete Player
	delete g_player;

	// Delete Environment
	delete g_environment;
}

void Camera::update(int delta)
{ 
	// Call the usual Container update
	EntityContainer::update(delta);
	
	// Center the camera onto the player
	CenterOnPlayer(); 
}

void Camera::render(void)
{
	g_environment->RenderBottom();
	g_player->e_render();
	g_environment->RenderTop();
}

void Camera::CenterOnPlayer()
{
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

Directions<bool> Camera::GetEdgeBools(XY _pos)
{
	_pos.RoundToInt();

	Directions<bool> r_directions = Directions<bool>(
		_pos.y >= 0,
		_pos.y <= SCREEN_HEIGHT - WORLD_HEIGHT * TILE_SIZE,
		_pos.x >= 0,
		_pos.x <= SCREEN_WIDTH  - WORLD_WIDTH * TILE_SIZE);

	return r_directions;
}

void ZoomToWidth(const int width)
{
	// Zoom to a level that fits the given width, in terms of tiles
}