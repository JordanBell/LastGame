#pragma once
#include "entity.h"
#include <list>

class EntityContainer : public Entity
{
public:
	EntityContainer(float x, float y) : Entity(x, y) {}
	~EntityContainer(void) {}

	void addChild(Entity* child) { children.push_back(child); child->setParent(this); }

	// Overriden Entity Functions
	virtual void render(void);
	void move(int _x, int _y);

protected:
	std::list<Entity*> children;
};