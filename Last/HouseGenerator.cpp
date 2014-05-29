#pragma once
#pragma warning(disable: 4715)
#include "HouseGenerator.h"
#include "Config.h"
#include "House.h"

void HouseGenerator::generate(void)
{
	// Warning: Not a very smart calculation on the number of houses allowed on the screen.
	Dimensions maxHouseDimensions(20, 20);

	XY numHouses = WORLD_DIMENSIONS / maxHouseDimensions; // Number of houses in X and Y direction
	numHouses.RoundToInt();

	for (int i = 0; i < numHouses.x; i++)
	{
		for (int j = 0; j < numHouses.y; j++)
		{
			// Get the size of this house
			//HouseSize size = ComputeRandomSize();
			const int numRooms = rand() % 3;

			// Compute the position of this house (in pixels)
			Coordinates gridPos(i, j);
			int separation(2);
			Coordinates position = gridPos * maxHouseDimensions + separation;

			House h(position, maxHouseDimensions, numRooms);
		}
	}
}