#include "WorldBuilder.h"
#include "HouseGenerator.h"

void WorldBuilder::build()
{
	// Default tiles (grass, surrounded by a wall so that the player can't escape)
	BuildBorderedRectangle<GrassTile, WORLD_BORDER>(XY(0, 0), XY(WORLD_WIDTH, WORLD_HEIGHT));

	HouseGenerator hg = HouseGenerator();
	hg.run();
}

void WorldBuilder::BuildRoom(XY pos, XY dimensions, bool randomDoorway)
{
	// Draw the border
	BuildBorderedRectangle<StoneFloorTile, StoneWallTile>(pos, dimensions);

	if (randomDoorway) BuildRandomDoorway(pos, dimensions);
}

void WorldBuilder::BuildRandomDoorway(XY pos, XY dimensions)
{
	// Find where along the wall the doorway should go
	XY doorPos = XY(0, 0);
	bool isOnHorizontal = rand() % 2;

	// If one side can't accomodate a door, pick the other
	bool horizontalValid = dimensions.x > 3;
	bool verticalValid	 = dimensions.y > 3;

	if (isOnHorizontal && horizontalValid) 
	{
		// Where along the sides
		doorPos.y = pos.y + (rand() % ((int)dimensions.y-3)) + 1;
			
		// Left or right side?
		bool left = rand() % 2;

		doorPos.x = left ? pos.x : 
							pos.x + dimensions.x-1;
	}
	else if (verticalValid)
	{
		// Where along the wall
		doorPos.x = pos.x + (rand() % ((int)dimensions.x-3)) + 1;
		
		// Top or bottom?
		bool top = rand() % 2;

		doorPos.y = top ? pos.y : 
							pos.y + dimensions.y-1;
	}
	else {
		printf("Square too small to add a door.");
		return;
	}

	// Get the dimensions of the door based on which side it's on
	XY doorDimensions = XY(isOnHorizontal? 1 : 2,
							isOnHorizontal? 2 : 1);
		
	// Build the door
	BuildRectangle<StoneFloorTile>(doorPos, doorDimensions);
}

template <class T_Fill, class T_Border>
//template <class T_Border>
void WorldBuilder::BuildBorderedRectangle(XY pos, XY dimensions)
{
	// Draw the border
	BuildRectangle<T_Border>(pos, dimensions, false);
	// Draw the fill
	BuildRectangle<T_Fill>(pos+1, dimensions-2, true);
}

template <class T>
void WorldBuilder::BuildRectangle(XY pos, XY dimensions, bool filled)
{
	for (int i = pos.x; i < pos.x + dimensions.x; i++)
	{
		for (int j = pos.y; j < pos.y + dimensions.y; j++)
		{
			if (filled) AddTileTo<T>(XY(i, j));
			else
			{
				XY upperBounds = pos + dimensions - 1;
				bool xEdge = ((i == pos.x) || (i == upperBounds.x));
				bool yEdge = ((j == pos.y) || (j == upperBounds.y));

				if (xEdge || yEdge) AddTileTo<T>(XY(i, j));
			}
		}
	}
}

template <class T>
void WorldBuilder::AddTileTo(XY pos)
{
	T* tile = new T(pos.x, pos.y);
	g_environment->tiles[(int)pos.x][(int)pos.y] = tile;
	g_environment->addChild(tile);
}
