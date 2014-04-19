#pragma once
#include "entity.h"
#include <list>

class EntityContainer : public Entity
{
public:
	EntityContainer(int x, int y) : Entity(x, y) {}
	~EntityContainer(void) {}

	void addChild(Entity* child) { children.push_back(child); /*child->setParent(this);*/ }
	virtual void render(void);

protected:
	std::list<Entity*> children;
};