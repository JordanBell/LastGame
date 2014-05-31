#include "DoorAnimation.h"

void DoorAnimation::Open(void)
{
	// Increase cycle on update
	animateOpen = true;
	Start();
}

void DoorAnimation::Close(void)
{
	// Decrease cycle on update
	animateOpen = false;
	Start();
}

void DoorAnimation::Update(void)
{
	if (animateOpen) m_iterator.Inc();
	else			 m_iterator.Dec();

	if (m_iterator.IsAtEnd()) Stop();
}