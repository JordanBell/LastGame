#include "House.h"
#include "WorldBuilder.h"

House::House(XY pos, XY allocatedSpace, int numRooms, E_Direction facingDirection) : pos(pos), allocatedSpace(allocatedSpace), numRooms(numRooms)
{
	// Create the biggest room in the center
	//WorldBuilder::BuildRoom(pos+1, allocatedSpace-2);
	XY mainRoomDim(allocatedSpace / 2);
	mainRoomDim.RoundToInt();

	XY mainRoomPos(pos + allocatedSpace*0.25f);
	mainRoomPos.RoundToInt();
	
	Room entireAreaRoom(pos, allocatedSpace);
	Room mainRoom(mainRoomPos, mainRoomDim);
	rooms.push_back(mainRoom);
}