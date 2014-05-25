#pragma once
#include "EntityContainer.h"
#include "AnimatedObject.h"

/*
A sprite is an EntityContainer that loops through an animation based on a cycle.
*/
class Sprite : public EntityContainer, public AnimatedObject
{

public:
	Sprite(int x, int y) : EntityContainer(x, y) {}
	~Sprite(void) {}

	// Set this sprite's skin, and render
	virtual void render(void) { set_skin(); EntityContainer::render(); }
};