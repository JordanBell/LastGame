#pragma once
#pragma warning(disable: 4715)
#include "HouseGenerator.h"
#include "WorldBuilder.h"
#include "Environment.h"
#include <stdlib.h>

HouseGenerator::HouseSize HouseGenerator::SMALL(XY(7, 7), 1);
HouseGenerator::HouseSize HouseGenerator::MEDIUM(XY(10, 10), 2);
HouseGenerator::HouseSize HouseGenerator::LARGE(XY(13, 13), 3);

void HouseGenerator::generate(void)
{
	// Warning: Not a very smart calculation on the number of houses allowed on the screen.
	XY maxHouseDimensions = LARGE.dimensions * (float)(1 + HOUSE_SIZE_DEVIATION);

	XY numHouses = WORLD_DIMENSIONS / maxHouseDimensions;
	numHouses.RoundToInt();

	for (int i = 0; i < numHouses.x; i++)
	{
		for (int j = 0; j < numHouses.y; j++)
		{
			// Get the size of this house
			HouseSize size = ComputeRandomSize();

			// Compute the position of this house (in pixels)
			XY gridPos = XY(i, j);
			
			XY position = gridPos * maxHouseDimensions + 3;

			//for (int k = 0; k < size.numRooms; k++)
			for (int k = 0; k < 1; k++)
			{
				// Build a room
				// The width and height ranges of size, based on the size dimensions, and the global size deviation percentage
				XY range = size.dimensions * (HOUSE_SIZE_DEVIATION*2);

				// Find random numbers within that range
				XY sizeDeviation((rand() % (int)range.x),
								 (rand() % (int)range.y));

				// Bring that deviation's median down to 0
				sizeDeviation -= range/2;

				// Compute the dimensions, using this info
				XY dimensions = size.dimensions + sizeDeviation;

				// Build the room with a random door (for now... random doors can't work with connected rooms)
				WorldBuilder::BuildRoom(position, dimensions);

				// Extra: Add a small room to the center of large houses
				if (size.numRooms == 3) WorldBuilder::BuildRoom(position + dimensions/4, dimensions/2);
			}
		}
	}
}

const HouseGenerator::HouseSize HouseGenerator::ComputeRandomSize(void)
{
	const int size = rand() % 3;
	switch (size)
	{
		case 0: return SMALL;
		case 1: return MEDIUM;
		case 2: return LARGE;
	}
}