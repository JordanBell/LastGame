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

	// Move this Entity and, all of its children, by a displacement
	void move(XY displacement);

protected:
	std::list<Entity*> children; // A list of the child Entities within this container.
};