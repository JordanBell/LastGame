#pragma once
#include "entity.h"
#include <list>

class EntityContainer : public Entity
{
public:
	EntityContainer(float x, float y) : Entity(x, y) {}
	~EntityContainer(void);

	// Add a child entity to this container
	void addChild(Entity* child) { children.push_back(child); child->setParent(this); }
	
	// Render this entity, as well as the children entities
	virtual void render(void);
	
	// Update this entity, as well as the children entities
	virtual void update(int delta);

	// Whether or not this, or any of its children, are on screen.
	bool IsOnScreen(void);

protected:
	std::list<Entity*> children; // A list of the child Entities within this container.
};