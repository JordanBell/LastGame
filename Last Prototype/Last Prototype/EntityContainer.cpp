#include "EntityContainer.h"

EntityContainer::~EntityContainer()
{
	// Remove all of the children
	int numChildren = children.size();
	for (int i = 0; i < numChildren; i++)
		children.pop_back();
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

	/*for (Entity* child : children)
	{
		child->move(displacement);
	}*/
}
