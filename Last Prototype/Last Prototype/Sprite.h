#pragma once
#include "EntityContainer.h"

/*
A sprite is an EntityContainer that loops through an animation based on a cycle.
*/
class Sprite : public EntityContainer
{
public:
	Sprite(float x, float y) : EntityContainer(x, y), cycle(0) {}
	~Sprite(void) {}
<<<<<<< HEAD

	// Set this sprite's skin, and render
	virtual void render(void) { set_skin(); EntityContainer::render(); }
=======
	void render(void) { set_skin(); EntityContainer::render(); }
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete

protected:
	int cycle;
	int max_cycles;
	
	virtual void IncCycle(void) { cycle = (cycle >= (max_cycles-1)) ? 0 : cycle+1; }
<<<<<<< HEAD
	
	// Decrement the cycle down to 0, then back up to max_cycle-1
	virtual void DecCycle(void) { cycle = (cycle <= 0) ? max_cycles-1 : cycle-1; }

	// Set the skin (clip) of this sprite
	virtual void set_skin(void) {};
=======
	virtual void set_skin(void) = 0;
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
};