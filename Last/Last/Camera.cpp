#pragma once
#include "Camera.h"
#include "Player.h"
#include "toolkit.h"

Camera* g_camera = NULL;

Camera::Camera(void) : EntityContainer(WORLD_DIMENSIONS * TILE_SIZE)
{
	AddChild(g_environment);
	CenterOnPlayer();
}

Camera::~Camera(void)
{
	// Delete Player
	delete g_player;

	// Delete Environment
	delete g_environment;
}

void Camera::E_Update(const int delta)
{ 
	// Call the usual Container update
	EntityContainer::E_Update(delta);
	
	// Center the camera onto the player
	CenterOnPlayer(); 
}

void Camera::E_Render(void)
{
	g_environment->Render();
}

void Camera::CenterOnPlayer()
{
	// Get the coordinates that the camera would move to, to center on the player
	Coordinates screenCenter(g_windowSurface->w/2, g_windowSurface->h/2);
	Coordinates suggestedPos = screenCenter - g_player->pos;

	// Check to see if that would reveal any edges
	Directions<bool> edgeBools = GetEdgeBools(suggestedPos);

	// Check the validity for each axis
	bool canCenterX = (!edgeBools.left && !edgeBools.right);
	bool canCenterY = (!edgeBools.top  && !edgeBools.bottom);
		
	// Center on the valid axes
	if (canCenterX) pos.x = suggestedPos.x;
	if (canCenterY) pos.y = suggestedPos.y;
}

Directions<bool> Camera::GetEdgeBools(Coordinates _pos) const
{
	_pos.RoundToInt();

	const Directions<bool> r_directions(
		_pos.y >= 0,
		_pos.y <= g_windowSurface->h - WORLD_HEIGHT * TILE_SIZE,
		_pos.x >= 0,
		_pos.x <= g_windowSurface->w  - WORLD_WIDTH * TILE_SIZE);

	return r_directions;
}

void Camera::ZoomToWidth(const int newWidth)
{
	// Get the 1:1 size of the camera
	Dimensions maxSize = Dimensions(0);
	SDL_RenderGetLogicalSize(g_renderer, (int*)(&maxSize.x), (int*)(&maxSize.y));
	maxSize /= TILE_SIZE;
	
	// Scale to fit the new width
	float newScale = maxSize.x / newWidth;
	SDL_RenderSetScale(m_renderer, newScale, newScale);

	// Add BlitOffset to keep the center of the Camera's rendered size in the center of the screen
	m_blitOffset = (maxSize.x-newWidth) * TILE_SIZE;
}