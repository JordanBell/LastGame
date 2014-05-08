#pragma once
#include "Tools.h"

class HouseGenerator
{
public:
	// Contains information about the dimensions and number of rooms in the house.
	struct HouseSize {
		HouseSize(XY _dimensions, int _rooms) : dimensions(_dimensions), numRooms(_rooms) {}

		XY dimensions;
		int numRooms;
	};

	// Generate the house buildings
	static void generate(void);

private:
	static HouseSize SMALL, MEDIUM, LARGE; // House Size data

	// Get a random size from the above house sizes
	static const HouseSize ComputeRandomSize(void);
};

