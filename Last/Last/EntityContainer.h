#pragma once
#include "Entity.h"
#include <list>

class Entity;

class EntityContainer : public Entity
{
public:
	virtual ~EntityContainer(void);

	// Add a child entity to this container
	virtual void AddChild(Entity* child);
	
	// Render this entity
		// As well as the children entities
	virtual void E_Render(void);
	
	// Update this entity
		// As well as the children entities
	virtual void E_Update(const int delta);

	// Whether or not this in on the screen
		// Or if any of its children are on the screen.
	bool IsOnScreen(void) const;

	SDL_Renderer** GetRenderer() { return &m_renderer; }

protected:
	bool m_staticImage;
	SDL_Renderer* m_renderer;
	std::list<Entity*> children; // A list of the child Entities within this container.

	// Only be constructed by subclasses
	EntityContainer(const Dimensions& dimensions, const Coordinates& _pos = Coordinates(), bool staticImage = false);
};