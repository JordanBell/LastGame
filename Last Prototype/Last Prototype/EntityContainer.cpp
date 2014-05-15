#include "EntityContainer.h"

<<<<<<< HEAD
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

=======
// Render this entity, as well as the children entities
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
void EntityContainer::render(void)
{
	Entity::render();

	for (Entity* child : children)
<<<<<<< HEAD
		child->e_render();

}

bool EntityContainer::IsOnScreen(void) const
{
	if (Entity::IsOnScreen()) return true;
	else
	{
		for (Entity* child : children)
			if (child->IsOnScreen()) return true;
=======
	{
		child->render();
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
	}
}
<<<<<<< HEAD
=======

void EntityContainer::move(int _x, int _y)
{
	Entity::move(_x, _y);

	for (Entity* child : children)
	{
		child->move(_x, _y);
	}
}
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
