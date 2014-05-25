#pragma once
#include "Tools.h"

class HouseGenerator
{
public:
	// Contains information about the dimensions and number of rooms in the house.
	struct HouseSize {
		HouseSize(Dimensions _dimensions, int _rooms) : dimensions(_dimensions), numRooms(_rooms) {}

		Dimensions dimensions;
		int numRooms;
	};

	// Generate the house buildings
	static void generate(void);

private:
	// Get a random size from the above house sizes
	static const HouseSize ComputeRandomSize(void);
};

