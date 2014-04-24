#pragma once
#include "EntityContainer.h"

/*
A sprite is an EntityContainer that loops through an animation based on a cycle.
*/
class Sprite : public EntityContainer
{
public:
	Sprite(int x, int y) : EntityContainer(x, y), cycle(0) {}
	~Sprite(void) {}

	// Set this sprite's skin, and render
	void render(void) { set_skin(); EntityContainer::render(); }

protected:
	int cycle; // The index cycle through a cycling animation
	int max_cycles; // The max cycle value, after which cycle resets to 0
	
	// Increment the cycle up to its max_cycle, then drop back to 0
	virtual void IncCycle(void) { cycle = (cycle >= (max_cycles-1)) ? 0 : cycle+1; }

	// Set the skin (clip) of this sprite
	virtual void set_skin(void) = 0;
};