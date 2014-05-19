#pragma once
class AnimationIterator
{
public:
	AnimationIterator(int maxCycles) : m_cycle(0), m_max(maxCycles) {}
	~AnimationIterator(void) {}
	
	// Increment the cycle up to its max_cycle, then drop back to 0
	void Inc(void) { m_cycle = (m_cycle >= (m_max-1)) ? 0 : m_cycle+1; }
	
	// Decrement the cycle down to 0, then back up to max_cycle-1
	void Dec(void) { m_cycle = (m_cycle <= 0) ? m_max-1 : m_cycle-1; }

	bool IsAtEnd(void) { (m_cycle == 0) || (m_cycle == m_max-1); }

private:
	int m_cycle; // The index cycle through a cycling animation
	int m_max; // The max cycle value, after which cycle resets to 0
};

