#pragma once
#include "EntityContainer.h"
class Room
{
	XY pos;
	XY dimensions;

public:
	Room(const XY pos, const XY dimensions);
	~Room(void) {}
};