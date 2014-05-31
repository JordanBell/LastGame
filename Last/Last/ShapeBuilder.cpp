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

void ShapeBuilder::BuildLine(Coordinates start, 
							 Coordinates end, 
							 void (*drawFunction)(const Coordinates&))
{
	bool xEqual = (start.x == end.x);
	bool yEqual = (start.y == end.y);

	if (!xEqual && !yEqual) throw new std::runtime_error("Cannot draw diagonal lines.");


	// Refer to the differing coordinates
	float& differingStart = xEqual ?
							start.y :
							start.x;
	float& differingEnd = xEqual ?
						  end.y :
						  end.x;

	// Get a negative or positive 1, based on the direction of the line.
	int directionPolarity = (differingStart < differingEnd) ? 1 : -1; 

	// The coordinates for each tile drawn, copied from Start as to not alter the original.
	Coordinates tileCoords = start; 

	// i loops through the positions between the two points, in the direction of their differing coordinates.
	for (int i = differingStart; i != differingEnd + directionPolarity /*Inclusive*/; i += directionPolarity) 
	{
		if (xEqual) tileCoords.y = i; // Alter Y
		if (yEqual) tileCoords.x = i; // Alter X
		
		// Add a tile to that position
		(*drawFunction)(tileCoords);
	}
}

template <class Tile_Fill, class Tile_Border>
void ShapeBuilder::BuildBorderedRectangle(const Coordinates& pos, 
										  const Dimensions& dimensions, 
										  Layer layer)
{
	// Draw the border
	BuildTileRectangle<Tile_Border>(pos, dimensions, false, layer);
	// Draw the fill
	BuildTileRectangle<Tile_Fill>(pos+1, dimensions-2, true, layer);
}