#include "Room.h"
#include "WorldBuilder.h"
#include "ShapeBuilder.h"

using namespace ShapeBuilder;

Room::Room(const Coordinates pos, const Dimensions dimensions) 
	: pos(pos), dimensions(dimensions)
{
	WorldBuilder::BuildRoom(pos, dimensions);
}