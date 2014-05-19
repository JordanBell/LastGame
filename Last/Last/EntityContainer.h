#pragma once
#include "entity.h"
#include <list>

class EntityContainer : public Entity
{
public:
	EntityContainer(float x, float y);
	virtual ~EntityContainer(void);

	// Add a child entity to this container
	virtual void addChild(Entity* child);
	
	//// Render this entity, as well as the children entities
	//virtual void render(void);
	
	// Update this entity, as well as the children entities
	virtual void update(const int delta);

	// Whether or not this, or any of its children, are on screen.
	bool IsOnScreen(void) const;

protected:
	SDL_Texture* m_textureContainer;
	std::list<Entity*> children; // A list of the child Entities within this container.
};