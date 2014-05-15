#pragma once
#include "EntityContainer.h"
#include "Room.h"

class House
{
	XY pos;
	XY allocatedSpace;

	int numRooms;
	std::list<Room> rooms;

public:
	House(XY pos, XY allocatedSpace, int numRooms, E_Direction facingDirection = E_Direction::DOWN);
	~House(void) {}
};