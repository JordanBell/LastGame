#include "Room.h"
#include "WorldBuilder.h"
#include "GridTiles.h"

using namespace ShapeBuilder;

Room::Room(const XY pos, const XY dimensions) : pos(pos), dimensions(dimensions)
{
	WorldBuilder::BuildRoom(pos, dimensions);
}