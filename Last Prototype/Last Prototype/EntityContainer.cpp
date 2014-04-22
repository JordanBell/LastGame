#include "EntityContainer.h"

// Render this entity, as well as the children entities
void EntityContainer::render(void)
{
	Entity::render();

	for (Entity* child : children)
	{
		child->render();
	}
}

void EntityContainer::move(int _x, int _y)
{
	Entity::move(_x, _y);

	for (Entity* child : children)
	{
		child->move(_x, _y);
	}
}
