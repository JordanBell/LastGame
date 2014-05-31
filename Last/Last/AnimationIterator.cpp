#include "AnimationIterator.h"
#include "AnimationIteratorException.h"

void AnimationIterator::Inc()
{ 
	if (on) 
	{
		// If Inc() is exactly what should be done
		if (!m_circular || goingForward) // If the iteration is linear, just do it. If it is circular, and should be iterating forwards, Inc()
		{
			if (MAX) // If at max
			{
				if (m_circular) goingForward = false; // Change direction
				else m_cycle = 0; // Set to min
			}
			else
				m_cycle++; // Increment
		}
		else if (m_circular && !goingForward) // Iteration is circular, and should be iterating backward. Delegate to Dec()
		{
			Dec();
		}
	}			 
	else throw AnimationIteratorException("Iterator is off. Cannot increment."); }

void AnimationIterator::Dec()
{ 
	if (on) {
		// If Dec() is exactly what should be done
		if (!m_circular || !goingForward) // If the iteration is linear, just do it. If it is circular, and should be iterating backwards, Dec()
		{
			if (MIN) // If at min
			{
				if (m_circular) goingForward = true; // Change direction
				else m_cycle = m_max-1; // Set to max
			}
			else
				m_cycle--; // Decrement
		}
		else if (m_circular && goingForward) // Iteration is circular, and should be iterating forward. Delegate to Inc()
		{
			Inc();
		}
	}
	else throw AnimationIteratorException("Iterator is off. Cannot decrement."); 
}

void AnimationIterator::OverrideCycle(int newCycle) 
{ 
	// Check for invalid override
	if (newCycle < 0) 
		throw std::runtime_error("Cannot override the cycle with a negative number.");
	if (newCycle > (m_max-1)) 
		throw std::runtime_error("Cannot override the cycle beyond its Max Cycle.");
	
	// Override
	m_cycle = newCycle;
}