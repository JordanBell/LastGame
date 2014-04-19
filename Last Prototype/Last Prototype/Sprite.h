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
	void render(void) { set_skin(); EntityContainer::render(); }

protected:
	int cycle;
	int max_cycles;
	
	virtual void IncCycle(void) { cycle = (cycle >= (max_cycles-1)) ? 0 : cycle+1; }
	virtual void set_skin(void) = 0;
};