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

	// Return true, in order to delegate the check to the children in their own Render functions
	bool ShouldRender(void) override { return true; }

	// Whether or not this, or if any of its children, are on the screen
	bool IsOnScreen(void) override;

	// Override to return the EntityContainer's image as an ImageTarget
	virtual ImageTarget& GetImage() override final { return m_imageTarget; }

protected:
	ImageTarget m_imageTarget;
	bool m_staticImage;
	list< unique_ptr<Entity> > children; // A list of the child Entities within this container.

	// EntityContainers can only be constructed by subclasses
	EntityContainer(const Dimensions& dimensions, const Coordinates& _pos = Coordinates(0, 0), bool staticImage = false);

	// Construct a container with all information for Entity construction provided.
	EntityContainer(const Dimensions& dimensions, 
					// Entity arguments
					const Coordinates& _pos, 
					const Coordinates& blitOffset, 
					const SSID& spriteSheetID, 
					const EntityFormat& format,
					SDL_Rect* clip = nullptr,
					AnimationModule* personalisedAnimationModule = nullptr, 
					bool staticImage = false);

	// Render this entity, as well as the children entities
	virtual void E_Render(void);
	
	// Update the children entities.
	virtual void E_Update(const int delta);

	// Add children to itself when first updated.
	virtual void InitAddChildren(void) {}

private:
	bool m_childrenInitiallyAdded;
};