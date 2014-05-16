#pragma once
class AnimatedObject
{
public:
	AnimatedObject(void) : cycle(0) {}
	virtual ~AnimatedObject(void) {}

protected:
	int cycle; // The index cycle through a cycling animation
	int max_cycles; // The max cycle value, after which cycle resets to 0
	
	// Increment the cycle up to its max_cycle, then drop back to 0
	virtual void IncCycle(void) { cycle = (cycle >= (max_cycles-1)) ? 0 : cycle+1; }
	
	// Decrement the cycle down to 0, then back up to max_cycle-1
	virtual void DecCycle(void) { cycle = (cycle <= 0) ? max_cycles-1 : cycle-1; }

	// Set the skin (clip) of this sprite
	virtual void set_skin(void) {};
};

