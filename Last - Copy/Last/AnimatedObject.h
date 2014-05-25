#pragma once
#include "AnimationIterator.h"

class AnimatedObject
{
public:
	AnimatedObject(int maxCycles) : cycle(maxCycles) {}
	virtual ~AnimatedObject(void) {}

protected:
	AnimationIterator cycle;

	// Set the skin (clip) of this sprite
	virtual void set_skin(void) {};
};

