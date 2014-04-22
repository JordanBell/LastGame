#pragma once
#include "HouseGenerator.h"
#include "Environment.h"
#include <stdlib.h>

void HouseGenerator::run(void)
{
	// Warning: Not a very smart calculation on the number of houses allowed on the screen.
	XY numHouses = XY(
		WORLD_WIDTH  / (LARGE.w + 5),
		WORLD_HEIGHT / (LARGE.h + 5)); 

	for (int i = 0; i < numHouses.x; i++)
	{
		for (int j = 0; j < numHouses.y; j++)
		{
			HouseSize size = ComputeRandomSize();
			XY* position = new XY(
				(i * LARGE.w*(1+HOUSE_SIZE_DEVIATION)) +5, 
				(j * LARGE.h*(1+HOUSE_SIZE_DEVIATION)) +5);
			
			//for (int k = 0; k < size.numRooms; k++)
			for (int k = 0; k < 1; k++)
			{
				// Build a room
				// The width and height ranges of size, based on the size w and h, and the global size deviation percentage
				XY range(
					HOUSE_SIZE_DEVIATION*2 * size.w, 
					HOUSE_SIZE_DEVIATION*2 * size.h);

				// Find random numbers within that range, with a median at 0
				XY sizeDeviation(
					(rand() % (int)range.x) - range.x/2, 
					(rand() % (int)range.y) - range.y/2);

				int width = size.w + sizeDeviation.x;
				int height = size.h + sizeDeviation.y;

				// Build the room with a random door (for now... random doors can't work with connected rooms... yet)
				g_environment->BuildRoom(position->x, position->y, width, height, true);

				if (size.numRooms == 3) g_environment->BuildRoom(position->x + width/4, position->y + height/4, width/2, height/2, true);
			}
		}
	}
}

HouseGenerator::HouseSize HouseGenerator::ComputeRandomSize(void)
{
	int size = rand() % 3;
	switch (size)
	{
		case 0: return SMALL;
		case 1: return MEDIUM;
		case 2: return LARGE;
	}

	//return LARGE;
}