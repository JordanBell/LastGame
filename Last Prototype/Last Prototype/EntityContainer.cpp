#include "EntityContainer.h"

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
