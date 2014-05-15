#include "EntityContainer.h"

EntityContainer::~EntityContainer()
{
	// Remove all of the children
	int numChildren = children.size();
	for (int i = 0; i < numChildren; i++)
		children.pop_back();
}

void EntityContainer::update(int delta)
{
	Entity::update(delta);

	for (Entity* child : children)
		child->update(delta);
}

void EntityContainer::render(void)
{
	Entity::render();

	for (Entity* child : children)
		child->e_render();

}

bool EntityContainer::IsOnScreen(void) const
{
	if (Entity::IsOnScreen()) return true;
	else
	{
		for (Entity* child : children)
			if (child->IsOnScreen()) return true;
	}

	return false;
}
