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
