#include "DoorAnimation.h"

void DoorAnimation::Open(void)
{
	// Increase cycle on update
	//cycleFunction = &(m_iterator.Inc);
	animateOpen = true;
	Start();
}

void DoorAnimation::Close(void)
{
	// Decrease cycle on update
	//cycleFunction = &(m_iterator.Dec);
	animateOpen = false;
	Start();
}

void DoorAnimation::Update(void)
{
	//cycleFunction(); // Iterate animation
	if (animateOpen) m_iterator.Inc();
	else			 m_iterator.Dec();

	if (m_iterator.IsAtEnd()) Stop();
}