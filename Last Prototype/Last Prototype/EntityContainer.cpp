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
	if (ShouldRenderImage()) Entity::render();

	for (Entity* child : children)
	{
		child->e_render();
	}
}

bool EntityContainer::IsOnScreen(void)
{
	if (Entity::IsOnScreen()) return true;
	else
	{
		for (Entity* child : children)

		{
			if (child->IsOnScreen()) return true;
		}
	}

	return false;
}

void EntityContainer::move(XY displacement)
{
	Entity::move(displacement);

	for (Entity* child : children)
	{
		child->move(displacement);
	}
}
