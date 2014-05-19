#include "EntityContainer.h"

EntityContainer::EntityContainer(float x, float y) : Entity(x, y) 
{
	// Initialise the container texture
	m_textureContainer = SDL_CreateTexture(	g_renderer, 
											SDL_PIXELFORMAT_RGBA8888, 
											SDL_TEXTUREACCESS_STREAMING, 
											WINDOWED_SCREEN_RES.x,
											WINDOWED_SCREEN_RES.y);
}

EntityContainer::~EntityContainer()
{
	// Remove all of the children
	int numChildren = children.size();
	for (int i = 0; i < numChildren; i++)
		children.pop_back();
}

void EntityContainer::addChild(Entity* child) 
{ 
	children.push_back(child); 
	child->setParent(this); 
}


void EntityContainer::update(int delta)
{
	Entity::update(delta);

	for (Entity* child : children)
		child->update(delta);
}

// Removed, as its children are only rendered once, onto this container's texture. Leave render as is from Entity
//void EntityContainer::render(void)
//{
//	Entity::render();
//
//	for (Entity* child : children)
//		child->e_render();
//}

bool EntityContainer::IsOnScreen(void) const
{
	if (Entity::IsOnScreen()) return true;
	else
	{
		for (Entity* child : children)
			if (child->IsOnScreen()) return true;
	}

	return false;
}
