#include "NPC.h"

void NPC::E_Update(const int delta)
{
	if (!m_moving)
	{
		int direction = rand() % 240;

		if (direction < 4) Walk((E_Direction)direction);
	}

	Traveller::E_Update(delta);
}