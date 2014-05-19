#include "DoorAnimation.h"

void DoorAnimation::Open(void)
{
	// Increase cycle on update
	cycleFunction = m_iterator.Inc;
	Start();
}

void DoorAnimation::Close(void)
{
	// Decrease cycle on update
	cycleFunction = m_iterator.Dec;
	Start();
}

void DoorAnimation::Update(void)
{
	cycleFunction(); // Iterate animation
	if (m_iterator.IsAtEnd()) Stop();
}