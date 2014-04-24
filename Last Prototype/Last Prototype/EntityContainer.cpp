#include "EntityContainer.h"

EntityContainer::~EntityContainer()
{
	// Delete and remove all of the children
	while (children.size() > 0)
	{
		delete children.front();
		children.pop_front();
	}
}

void EntityContainer::render(void)
{
	Entity::render();

	for (Entity* child : children)
	{
		child->render();
	}
}

void EntityContainer::move(XY displacement)
{
	Entity::move(displacement);

	for (Entity* child : children)
	{
		child->move(displacement);
	}
}
