#pragma once
#include "entity.h"

// A door which opens and closes on interact
class Door : public Entity {
public:
	Door(const Coordinates& _pos);

protected:
	// On interact, open the door.
	void E_OnInteract(void);
	// Move through when the door is fully open.
	bool E_CanMoveThrough(void);

private:
	bool open; // Whether or not this door is currently open.
};