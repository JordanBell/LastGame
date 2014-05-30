#pragma once
#include "Camera.h"
#include "Player.h"
#include "toolkit.h"

Camera* g_camera = nullptr;

Camera::Camera(void) : EntityContainer(WORLD_DIMENSIONS * TILE_SIZE) {}

Camera::~Camera(void)
{
	// Delete Player
	delete g_player;

	// Delete Environment
	delete g_environment;
}

void Camera::InitChildren(void)
{
	AddChild(g_environment);
	CenterOnPlayer();
}

void Camera::E_Update(const int delta)
{ 
	// Call the usual Container update
	EntityContainer::E_Update(delta);
	
	// Center the camera onto the player
	CenterOnPlayer(); 
}

void Camera::CenterOnPlayer()
{
	// Get the coordinates that the camera would move to, to center on the player
	Coordinates screenCenter(LOGICAL_SIZE.x/2, LOGICAL_SIZE.y/2);
	Coordinates suggestedPos = screenCenter - g_player->pos;

	// Check to see if that would reveal any edges
	Directions<bool> edgeBools = GetEdgeBools(suggestedPos);

	// Check the validity for each axis
	bool canCenterX = (!edgeBools.left && !edgeBools.right);
	bool canCenterY = (!edgeBools.top  && !edgeBools.bottom);
		
	// Center on the valid axes
	if (canCenterX) pos.x = suggestedPos.x;
	if (canCenterY) pos.y = suggestedPos.y;

	//printf("Camera pos (%f, %f).\n", pos.x, pos.y);
}

Directions<bool> Camera::GetEdgeBools(Coordinates _pos) const
{
	_pos.RoundToInt();

	const Directions<bool> r_directions(
		_pos.y >= 0,
		_pos.y <= LOGICAL_SIZE.y - (WORLD_HEIGHT * TILE_SIZE),
		_pos.x >= 0,
		_pos.x <= LOGICAL_SIZE.x - (WORLD_WIDTH * TILE_SIZE));

	return r_directions;
}

void Camera::ZoomToWidth(const int newWidth)
{
	// Get the 1:1 size of the camera
	Dimensions maxSize = g_renderer->GetLogicalSize();
	maxSize /= TILE_SIZE;
	
	// Scale to fit the new width
	float newScale = maxSize.x / newWidth;
	g_renderer->SetScale(newScale);

	// Add BlitOffset to keep the center of the Camera's rendered size in the center of the screen
	m_blitOffset = (maxSize.x-newWidth) * TILE_SIZE;
}