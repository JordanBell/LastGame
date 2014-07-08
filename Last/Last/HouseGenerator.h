#pragma once
#include "Tools.h"

class HouseGenerator
{
public:
	// Contains information about the dimensions and number of rooms in the house.
	struct HouseSize {
		HouseSize(Dimensions _dimensions, int _rooms) 
			: dimensions(_dimensions), numRooms(_rooms) {}

		Dimensions dimensions;
		int numRooms;
	};

	struct RoomData {
		RoomData(Dimensions dimensions, Directions<int> doorPositions)
			: dimensions(dimensions), doorPositions(doorPositions) {}

		Dimensions dimensions; // Exterior dimensions, walls included

		/* 
		Door positions on each of the four walls. If value is -1 (default), there is no door.
		Left and right: Distance from top.
		Top and bottom: Distance from left.
		*/
		Directions<int> doorPositions; 
	};

	// Generate the house buildings.
	static void GenerateAll(void);

	// Generate a single room.
	static void GenerateRoom(const Coordinates& origin, const RoomData& data);

private:
	// Get a random size from the above house sizes.
	static const HouseSize ComputeRandomSize(void); /* To be implemented. */ 
};

