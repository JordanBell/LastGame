#pragma once
#define MIN (m_cycle == 0)
#define MAX (m_cycle == m_max-1)

class AnimationIterator
{
	friend class AnimationModule;

	AnimationIterator(int maxCycles, bool circular = false) : m_cycle(0), m_max(maxCycles), m_circular(circular) {}
	~AnimationIterator(void) {}

	int m_cycle; // The index cycle through a cycling animation
	int m_max;	 // The max cycle value, after which cycle resets to 0
	bool on;	 // Whether this iterator is on or off.
	bool m_circular; // If set as true, alternate between Inc and Dec when at max and min
	bool goingForward; // Inc() when true, Dec() when false
	
	void TurnOn (void) { on = true; }
	void TurnOff(void) { on = false; }

public:
	
	// Increment the cycle up to its max_cycle, then drop back to 0
	void Inc(void);
	
	// Decrement the cycle down to 0, then back up to max_cycle-1
	void Dec(void);

	// Return whether or not the cycle has reached an edge value, either MIN or MAX.
	bool IsAtEnd(void) { return (MIN || MAX); }
};

