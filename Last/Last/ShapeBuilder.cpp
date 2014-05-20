#include "ShapeBuilder.h"

void ShapeBuilder::BuildRectangle(const Coordinates& pos, const Dimensions& dimensions, void (*drawFunction)(const Coordinates&), bool filled)
{
	for (float i = pos.x; i < pos.x + dimensions.x; i++)
	{
		for (float j = pos.y; j < pos.y + dimensions.y; j++)
		{
			if (filled) (*drawFunction)(Coordinates(i, j));
			else
			{
				Coordinates upperBounds = pos + dimensions - 1;
				const bool xEdge = ((i == pos.x) || (i == upperBounds.x));
				const bool yEdge = ((j == pos.y) || (j == upperBounds.y));

				if (xEdge || yEdge) (*drawFunction)(Coordinates(i, j));
			}
		}
	}
}

void ShapeBuilder::BuildLine(Coordinates start, Coordinates end, void (*drawFunction)(const Coordinates&))
{
	bool xEqual = (start.x == end.x);
	bool yEqual = (start.y == end.y);

	// Point to the differing coordinates
	float* differingStart;
	float* differingEnd;

	// Point to the coordinates that differ
	if (xEqual)
	{
		differingStart = &start.y;
		differingEnd = &end.y;
	}
	else if (yEqual)
	{
		differingStart = &start.x;
		differingEnd = &end.x;
	}
	else throw new std::runtime_error("Cannot draw diagonal lines.");

	int directionPolarity = (*differingStart < *differingEnd) ? 1 : -1; // Negative or positive, based on the direction of the line

	Coordinates tileCoords = start; // The coordinates for each tile drawn
	for (int i = *differingStart; i != *differingEnd + directionPolarity /*Inclusive*/; i += directionPolarity) // i loops through the positions between the two points, in the direction of their differing coordinates
	{
		if (xEqual) tileCoords.y = i; // Alter Y
		if (yEqual) tileCoords.x = i; // Alter X
		
		// Add a tile to that position
		(*drawFunction)(tileCoords);
	}
}