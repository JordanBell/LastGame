#pragma once
#include "Entity.h"
#include "EntityContainer.h"
#include "toolkit.h"
#include "Resources.h"
#include "Player.h" // For recognizing self as g_player

Entity::Entity(const Coordinates& _pos,
		   const Coordinates& blitOffset,
		   SSID spriteSheetID,
		   EntityFormat format,	
		   SDL_Rect* clip,
		   AnimationModule* personalisedAnimationModule) 
		   : m_image(spriteSheetID, clip, !format[ANIMATED]), 
		     m_format(format), 
			 m_blitOffset(blitOffset), 
			 a_module(personalisedAnimationModule), 
			 parent(nullptr)
{
	// If not GridIndependent, take _pos as a grid position. Otherwise, take as is
	pos = (m_format[GRID_INDEPENDENT]) ? _pos : _pos*TILE_SIZE;

	// Check animation dependancies
	if (format[ANIMATED] && !a_module) throw ModuleMisuseException("Animated Entities must be initialised with an Animation Module.");
	if (!format[ANIMATED] && a_module) throw ModuleMisuseException("You cannot pass an Animation Module to a non-animated Entity.");
}	

Entity::~Entity(void)
{
	delete a_module;
}

void Entity::SetParent(EntityContainer* p) 
{ 
	parent = p; 
	GetImage().SetTarget(&(parent->GetImage()));
}

void Entity::BlitToParent()
{
	Coordinates blitPos = GetBlittingPos();
	GetImage().RenderToTarget(blitPos);
}

Coordinates Entity::GetAbsolutePos(void) const
{
	if (parent == nullptr) return pos;
	else
	{
		// Add the parent's blitting x to this one
		return pos + parent->GetAbsolutePos();
	}
}

Coordinates Entity::GetGridPosition(const Coordinates& _pos)
{
	Coordinates r_gridPosition = _pos;

	// Round to the nearest multiple of TILE_SIZE
	r_gridPosition /= (float)TILE_SIZE;
	r_gridPosition.RoundToNearest();

	return r_gridPosition;
}

bool Entity::IsOnScreen(void)
{
	// Get the size of the texture
	const Dimensions imageSize = GetImage().Size();
	if (imageSize.Contains(0)) return false;

	// Get its position
	const Coordinates absolutePos = GetAbsolutePos();

	// Get the edges of the entity
	const Directions<float>entityEdges(RectFromXY(absolutePos, imageSize));

	// Return whether or not any of the edges peek over the screen
	return ((entityEdges.top	< LOGICAL_SIZE.y) &&
			(entityEdges.left	< LOGICAL_SIZE.x) &&
			(entityEdges.bottom > 0)			  &&
			(entityEdges.right	> 0));
}

bool Entity::ShouldRenderImage(void)
{
	bool validImage = GetImage().ShouldRender();
	bool onScreen = IsOnScreen();

	return (validImage && onScreen);
}


/**** CHECKED DELEGATION FUNCTIONS ****/

void Entity::Update(const int delta)
{ 
	if (m_format[UPDATES]) 
		E_Update(delta);
}

void Entity::Render(void)
{ 
	// Update animation information prior to rendering.
	if (m_format[ANIMATED])
	{
		a_module->UpdateModule(); 
		//GetImage().SetClip( a_module->GetClip() );

		SDL_Rect testRect = { 0, 0, 32, 32 };
		GetImage().SetClip( &testRect );
	}

	// Make visible if deemed necessary
	if (ShouldRender()) E_Render();
}

void Entity::OnInteract(void)
{
	if (m_format[INTERACTABLE]) 
		E_OnInteract();
}

bool Entity::CanMoveThrough(void)
{
	if (m_format[TANGIBLE])
		return E_CanMoveThrough(); // Let the implementation decide
	else
		return true;
}