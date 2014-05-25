#include "EntityContainer.h"
#include "toolkit.h"
#include "Config.h"

EntityContainer::EntityContainer(const Dimensions& dimensions, const Coordinates& _pos, bool staticImage) 
	: Entity(_pos, Coordinates(0, 0), SSID_NULL, CONTAINER_FRMT), m_staticImage(staticImage)
{
	// ReInitialise the texture image as an ImageStreamer
	m_image = ImageStreamer(NULL);
}

EntityContainer::~EntityContainer()
{
	// Remove all of the children
	int numChildren = children.size();
	for (int i = 0; i < numChildren; i++)
		children.pop_back();
}

void EntityContainer::AddChild(Entity* child) 
{ 
	children.push_back(child); 
	child->SetParent(this); 

	// If static image, just blit now, as it won't re-blit on every frame
	if (m_staticImage) child->BlitToParent();
}


void EntityContainer::E_Update(int delta)
{
	for (Entity* child : children)
		child->Update(delta);
}

// Removed, as its children are only rendered once, onto this container's texture. Leave render as is from Entity
void EntityContainer::E_Render(void)
{
	// Check if own image should render
	if (ShouldRenderImage()) Entity::E_Render();

	// Only render children if the image is dynamic
	if (!m_staticImage)
	{
		for (Entity* child : children)
			child->Render(); // Render, not E_Render, as the child must go through the check again
	}
}

bool EntityContainer::IsOnScreen(void) const
{
	if (Entity::IsOnScreen()) return true;
	else if (!m_staticImage)
	{
		for (Entity* child : children)
			if (child->IsOnScreen()) return true;
	}

	return false;
}
