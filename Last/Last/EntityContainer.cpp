#include "EntityContainer.h"
#include "toolkit.h"
#include "Config.h"

EntityContainer::EntityContainer(const Dimensions& dimensions, const Coordinates& _pos, bool staticImage) 
	: Entity(_pos, Coordinates(), SSID_NULL, CONTAINER_FRMT), m_staticImage(staticImage)
{
	// ReInitialise the texture so that it's an empty texture with Streaming access. 
	m_image = SDL_CreateTexture(g_renderer, 
								SDL_PIXELFORMAT_RGBA8888, 
								SDL_TEXTUREACCESS_STREAMING, 
								dimensions.x,
								dimensions.y);
	m_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	// Have the member renderer render to the m_image
	SDL_SetRenderTarget(m_renderer, m_image);
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
	Entity::E_Update(delta);

	for (Entity* child : children)
		child->Update(delta);
}

// Removed, as its children are only rendered once, onto this container's texture. Leave render as is from Entity
void EntityContainer::E_Render(void)
{
	Entity::E_Render();

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
