#pragma once
#pragma warning(disable: 4715)
#include "HouseGenerator.h"
#include "House.h"
#include "WorldBuilder.h"
#include "Environment.h"
#include <stdlib.h>

void HouseGenerator::generate(void)
{
	// Warning: Not a very smart calculation on the number of houses allowed on the screen.
	XY maxHouseDimensions(20, 20);

	XY numHouses = WORLD_DIMENSIONS / maxHouseDimensions;
	numHouses.RoundToInt();

	for (int i = 0; i < numHouses.x; i++)
	{
		for (int j = 0; j < numHouses.y; j++)
		{
			// Get the size of this house
			//HouseSize size = ComputeRandomSize();
			const int numRooms = rand() % 3;

			// Compute the position of this house (in pixels)
			XY gridPos(i, j);
			int separation(2);
			XY position = gridPos * maxHouseDimensions + separation;

			House h(position, maxHouseDimensions, numRooms);
		}
	}
}