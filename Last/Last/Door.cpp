#include "Door.h"
#include "DoorAnimation.h"
#include "Config.h"

Door::Door(const Coordinates& _pos) 
	: Entity(_pos, 
			 Coordinates(0, -TILE_SIZE/2), 
			 SSID_DOOR, 
			 DOOR_FRMT, 
			 nullptr, 
			 new DoorAnimation()),
	open(false) {}

void Door::E_OnInteract(void)
{
	// Allow interact if door is not already animating
	if (!a_module->IsAnimating())
	{
		open = !open; // Toggle
		dynamic_cast<DoorAnimation*>(a_module)->StartDoor(open); // Start the animation
	}
}

bool Door::E_CanMoveThrough(void)
{
	// Can move through if the door is open, and not in the process of animating
	return (!a_module->IsAnimating() && open);
}
