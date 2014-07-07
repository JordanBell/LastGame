#include "EntityContainer.h"
#include "toolkit.h"
#include "Config.h"

EntityContainer::EntityContainer(const Dimensions& dimensions, const Coordinates& _pos, bool staticImage) 
	: Entity(_pos, Coordinates(0, 0), SSID_NULL, CONTAINER_FRMT), 
	m_staticImage(staticImage),
	m_imageTarget(dimensions, staticImage),
	m_childrenInitiallyAdded(false){}

EntityContainer::EntityContainer(const Dimensions& dimensions, 
								 // Entity arguments
								 const Coordinates& _pos, 
								 const Coordinates& blitOffset, 
								 const SSID& spriteSheetID, 
								 const EntityFormat& format,
								 SDL_Rect* clip,
								 AnimationModule* personalisedAnimationModule, 
								 bool staticImage) 
	: Entity(_pos, blitOffset, spriteSheetID, format, clip, personalisedAnimationModule), 
	m_staticImage(staticImage),
	m_imageTarget(dimensions, staticImage) {}

void EntityContainer::AddChild(Entity* child) 
{ 
	children.emplace_back(child);
	child->SetParent(this); 

	// If static image, just blit now, as it won't re-blit on every frame
	if (m_staticImage) child->BlitToParent();
}


void EntityContainer::E_Update(int delta)
{
	if (!m_childrenInitiallyAdded)
		InitAddChildren();

	for (auto& child : children)
		child->Update(delta);
}

// Removed, as its children are only rendered once, onto this container's texture. Leave render as is from Entity
void EntityContainer::E_Render(void)
{
	// Only render children if the image is dynamic
	if (!m_staticImage)
	{
		for (auto& child : children)
			child->Render(); // Render, not E_Render, as the child must go through the check again
	}
	
	// Check if own image should render
	if (ShouldRenderImage()) Entity::E_Render();
}

bool EntityContainer::IsOnScreen(void)
{
	if (Entity::IsOnScreen()) return true;
	else if (!m_staticImage)
	{
		for (auto& child : children)
			if ( child->IsOnScreen() ) return true;
	}

	return false;
}
