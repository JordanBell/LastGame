#include "House.h"
#include "WorldBuilder.h"

House::House(Coordinates pos, Dimensions allocatedSpace, int numRooms, E_Direction facingDirection) 
	: pos(pos), allocatedSpace(allocatedSpace), numRooms(numRooms)
{
	// Create the biggest room in the center
	//WorldBuilder::BuildRoom(pos+1, allocatedSpace-2);
	Dimensions mainRoomDim(allocatedSpace / 2);
	mainRoomDim.RoundToInt();

	Coordinates mainRoomPos(pos + allocatedSpace*0.25f);
	mainRoomPos.RoundToInt();
	
	Room entireAreaRoom(pos, allocatedSpace);
	Room mainRoom(mainRoomPos, mainRoomDim);
	rooms.push_back(mainRoom);
}