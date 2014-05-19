#include "Door.h"
#include "DoorAnimation.h"

Door::Door(const XY& _pos) 
	: Entity(_pos, 
			 XY(0, -TILE_SIZE/2), 
			 SSID_DOOR, 
			 DOOR_FRMT, 
			 NULL, 
			 new DoorAnimation()),
	open(false) {}

void Door::E_OnInteract(void)
{
	// Allow interact if door is not already animating
	if (!a_module->IsAnimating())
	{
		open = !open; // Toggle
		a_module->Start(); // Start the animation
	}
}

bool Door::E_CanMoveThrough(void)
{
	if (!a_module->IsAnimating() && open) return true;
	else return false;
}