#pragma once
#include "Entity.h"
#include "EntityContainer.h"
#include "toolkit.h"
#include "Resources.h"

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
	SetPosition(_pos);
	SetFormat(format);
}

Entity::Entity(const Coordinates& _pos,
		   const Coordinates& blitOffset,
		   Image image,
		   EntityFormat format,	
		   AnimationModule* personalisedAnimationModule) 
		   : m_image(image), 
		     m_format(format), 
			 m_blitOffset(blitOffset), 
			 a_module(personalisedAnimationModule), 
			 parent(nullptr)
{
	SetPosition(_pos);
	SetFormat(format);
}	

Entity::Entity(const Coordinates& _pos,
		   const Coordinates& blitOffset,
		   EntityFormat format,	
		   AnimationModule* personalisedAnimationModule) 
		   : m_image(SSID_NULL, nullptr, !format[ANIMATED]),
		     m_format(format), 
			 m_blitOffset(blitOffset), 
			 a_module(personalisedAnimationModule), 
			 parent(nullptr)
{
	SetPosition(_pos);
	SetFormat(format);
}	

Entity::~Entity(void)
{
	delete a_module;
}

void Entity::SetPosition(const Coordinates& _pos)
{
	// If not GridIndependent, take _pos as a grid position. Otherwise, take as is.
	pos = (m_format[GRID_INDEPENDENT]) ?
		  _pos : 
		  _pos*TILE_SIZE;
}

void Entity::CenterAround(Coordinates center, bool centerX, bool centerY)
{
	Dimensions size = GetImage().Size();

	// Center activated axis
	if (centerX) pos.x = center.x - (size.x / 2);
	if (centerY) pos.y = center.y - (size.y / 2);
}

void Entity::SetFormat(EntityFormat& format) 
{ 
	m_format = format; 

	// Check animation dependancies
	if (format[ANIMATED] && !a_module) throw ModuleMisuseException("Animated Entities must be initialised with an Animation Module.");
	if (!format[ANIMATED] && a_module) throw ModuleMisuseException("You cannot pass an Animation Module to a non-animated Entity.");
}


void Entity::SetParent(EntityContainer* p) 
{ 
	parent = p; 
	SetImageTarget();
}

inline void Entity::SetImageTarget(void) 
{ 
	if (parent)
		GetImage().SetTarget( &( parent->GetImage() ) ); 
}


void Entity::SetImage(Image& image) 
{ 
	m_image = image; 
	SetImageTarget();
}

void Entity::BlitToParent()
{
	Coordinates blitPos = GetBlittingPos();
	GetImage().RenderToTarget(blitPos);
}

void Entity::Animate(void)
{
	// Update module
	a_module->UpdateModule(); 

	// Update Clip rect
	UpdateClipFromAnimation();
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
	if (imageSize.Contains(0)) throw runtime_error("Width and/or height equal 0.");

	// Get its position
	const Coordinates onScreenPos = GetAbsolutePos() + m_blitOffset;

	// Get the edges of the entity
	const Directions<float>entityEdges(RectFromXY(onScreenPos, imageSize));

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
	if (m_format[ANIMATED])
		Animate();

	if (m_format[UPDATES]) 
		E_Update(delta);
}

void Entity::Render(void)
{ 
	// Make visible if deemed necessary
	if (ShouldRender()) 
		E_Render();
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