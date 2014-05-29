#pragma once
#include "EntityContainer.h"
#include "Room.h"

class House
{
	Coordinates pos;
	Dimensions allocatedSpace;

	int numRooms;
	std::list<Room> rooms;

public:
	House(Coordinates pos, Dimensions allocatedSpace, int numRooms, E_Direction facingDirection = E_Direction::DOWN);
	~House(void) {}
};