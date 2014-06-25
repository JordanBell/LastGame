#pragma once
#include "Entity.h"
#include <list>
#include <memory>
using namespace std;

class Entity;

class EntityContainer : public Entity
{
public:
	// Add a child entity to this container
	virtual void AddChild(Entity* child);

	// Always delegate children render checks to their Render functions
	virtual bool ShouldRender(void) const { return true; }

	// Whether or not this, or if any of its children, are on the screen
	bool IsOnScreen(void);

	// Override to return the EntityContainer's image as an ImageTarget
	virtual ImageTarget& GetImage() { return m_imageTarget; }

protected:
	ImageTarget m_imageTarget;
	bool m_staticImage;
	//std::list<Entity*> children; // A list of the child Entities within this container.
	list< unique_ptr<Entity> > children; // A list of the child Entities within this container.

	// Render this entity, as well as the children entities
	virtual void E_Render(void);
	
	// Update the children entities.
	virtual void E_Update(const int delta);

	// EntityContainers can only be constructed by subclasses
	EntityContainer(const Dimensions& dimensions, const Coordinates& _pos = Coordinates(0, 0), bool staticImage = false);
};