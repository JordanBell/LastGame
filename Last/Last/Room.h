#pragma once
#include "EntityContainer.h"
class Room
{
	Coordinates pos;
	Dimensions dimensions;

public:
	Room(const Coordinates pos, const Dimensions dimensions);
};