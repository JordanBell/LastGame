#include "WorldBuilder.h"
#include "HouseGenerator.h"

using namespace ShapeBuilder;

void WorldBuilder::build()
{
	// Default tiles (grass, surrounded by a wall so that the player can't escape)
	BuildBorderedRectangle<GrassTile, WORLD_BORDER>(XY(0, 0), XY(WORLD_WIDTH, WORLD_HEIGHT));

	HouseGenerator hg = HouseGenerator();
	//hg.run();

	BuildTestHouse(XY(WORLD_WIDTH/2-3, WORLD_HEIGHT/2-4));
}

template <class T>
void WorldBuilder::AddTileTo(XY pos, bool top, bool* setSolidityTo)
{
	// Create an object of that tile type
	T* tile = new T(pos.x, pos.y);

	if (setSolidityTo)
	{
		printf("Overriding solidity to: %d", setSolidityTo);
		tile->canMoveThrough = *setSolidityTo;
	}

	// Add the tile to the specified layer
	if (top) g_environment->AddTileToTop(tile);
	else	 g_environment->AddTileToBottom(tile);
}

void WorldBuilder::BuildTestHouse(XY pos)
{
	XY mainRoomDimensions(6, 7);
	
	// Main floor
	BuildRectangle<StoneFloorTile_LightBrown>(pos, mainRoomDimensions);
	// Left floor
	BuildRectangle<StoneFloorTile>(XY(pos.x-mainRoomDimensions.x+2, pos.y), XY(4, 8));
	// Right floor
	BuildRectangle<StoneFloorTile>(XY(pos.x+mainRoomDimensions.x, pos.y), XY(4, 8));
	// Entry way floor
	BuildRectangle<StoneFloorTile_LightBrown>(XY(pos.x+1, pos.y+mainRoomDimensions.y), XY(4, 2));

	// Black rectangle
	//BuildRectangle<Tile_Black>(pos-1, mainRoomDimensions+2, false, true);

	///////////// LEFT ROOM
	// Back Wall
	BuildColumn<WoodWallTile>(XY(pos.x-2, pos.y+mainRoomDimensions.y-8));
	BuildArchAbove<WoodWallTile>(XY(pos.x-3, pos.y+mainRoomDimensions.y-8));
	BuildColumn<WoodWallTile>(XY(pos.x-4, pos.y+mainRoomDimensions.y-8));
	BuildColumn<WoodWallTile>(XY(pos.x-5, pos.y+mainRoomDimensions.y-8));

	// Left Wall
	BuildColumn<WoodWallTile>(XY(pos.x-5, pos.y+mainRoomDimensions.y-7));
	BuildColumn<WoodWallTile>(XY(pos.x-5, pos.y+mainRoomDimensions.y-6));
	BuildColumn<WoodWallTile>(XY(pos.x-5, pos.y+mainRoomDimensions.y-5));
	BuildColumn<WoodWallTile>(XY(pos.x-5, pos.y+mainRoomDimensions.y-4));
	BuildColumn<WoodWallTile>(XY(pos.x-5, pos.y+mainRoomDimensions.y-3));
	BuildColumn<WoodWallTile>(XY(pos.x-5, pos.y+mainRoomDimensions.y-2));
	BuildColumn<WoodWallTile>(XY(pos.x-5, pos.y+mainRoomDimensions.y-1));
	BuildColumn<WoodWallTile>(XY(pos.x-5, pos.y+mainRoomDimensions.y));
	BuildColumn<WoodWallTile>(XY(pos.x-5, pos.y+mainRoomDimensions.y+1));

	// Front Wall
	BuildColumn<WoodWallTile>(XY(pos.x-2, pos.y+mainRoomDimensions.y+1));
	BuildArchAbove<WoodWallTile>(XY(pos.x-3, pos.y+mainRoomDimensions.y+1));
	BuildColumn<WoodWallTile>(XY(pos.x-4, pos.y+mainRoomDimensions.y+1));
	BuildColumn<WoodWallTile>(XY(pos.x-5, pos.y+mainRoomDimensions.y+1));

	///////////// RIGHT ROOM
	// Back Wall
	BuildColumn<WoodWallTile>(XY(pos.x+7, pos.y+mainRoomDimensions.y-8));
	BuildArchAbove<WoodWallTile>(XY(pos.x+8, pos.y+mainRoomDimensions.y-8));
	BuildColumn<WoodWallTile>(XY(pos.x+9, pos.y+mainRoomDimensions.y-8));
	BuildColumn<WoodWallTile>(XY(pos.x+10, pos.y+mainRoomDimensions.y-8));

	// Right Wall
	BuildColumn<WoodWallTile>(XY(pos.x+10, pos.y+mainRoomDimensions.y-7));
	BuildColumn<WoodWallTile>(XY(pos.x+10, pos.y+mainRoomDimensions.y-6));
	BuildColumn<WoodWallTile>(XY(pos.x+10, pos.y+mainRoomDimensions.y-5));
	BuildColumn<WoodWallTile>(XY(pos.x+10, pos.y+mainRoomDimensions.y-4));
	BuildColumn<WoodWallTile>(XY(pos.x+10, pos.y+mainRoomDimensions.y-3));
	BuildColumn<WoodWallTile>(XY(pos.x+10, pos.y+mainRoomDimensions.y-2));
	BuildColumn<WoodWallTile>(XY(pos.x+10, pos.y+mainRoomDimensions.y-1));
	BuildColumn<WoodWallTile>(XY(pos.x+10, pos.y+mainRoomDimensions.y));
	BuildColumn<WoodWallTile>(XY(pos.x+10, pos.y+mainRoomDimensions.y+1));

	// Back Wall
	BuildColumn<WoodWallTile>(XY(pos.x+7, pos.y+mainRoomDimensions.y+1));
	BuildArchAbove<WoodWallTile>(XY(pos.x+8, pos.y+mainRoomDimensions.y+1));
	BuildColumn<WoodWallTile>(XY(pos.x+9, pos.y+mainRoomDimensions.y+1));
	BuildColumn<WoodWallTile>(XY(pos.x+10, pos.y+mainRoomDimensions.y+1));

	///////////// MAIN ROOM
	// Back Wall
	BuildColumn<WoodWallTile>(XY(pos.x-1, pos.y+mainRoomDimensions.y-8));
	BuildColumn<WoodWallTile>(XY(pos.x, pos.y+mainRoomDimensions.y-8));
	BuildColumn<WoodWallTile>(XY(pos.x+1, pos.y+mainRoomDimensions.y-8));
	BuildColumn<WoodWallTile>(XY(pos.x+2, pos.y+mainRoomDimensions.y-8));
	BuildColumn<WoodWallTile>(XY(pos.x+3, pos.y+mainRoomDimensions.y-8));
	BuildColumn<WoodWallTile>(XY(pos.x+4, pos.y+mainRoomDimensions.y-8));
	BuildColumn<WoodWallTile>(XY(pos.x+5, pos.y+mainRoomDimensions.y-8));
	BuildColumn<WoodWallTile>(XY(pos.x+6, pos.y+mainRoomDimensions.y-8));
	
	//// Left Wall
	BuildColumn<WoodWallTile>(XY(pos.x-1, pos.y+mainRoomDimensions.y-8));
	BuildColumn<WoodWallTile>(XY(pos.x-1, pos.y+mainRoomDimensions.y-7));
	BuildColumn<WoodWallTile>(XY(pos.x-1, pos.y+mainRoomDimensions.y-6));

	BuildColumn<WoodWallTile>(XY(pos.x-1, pos.y+mainRoomDimensions.y-2));
	BuildColumn<WoodWallTile>(XY(pos.x-1, pos.y+mainRoomDimensions.y-1));
	BuildColumn<WoodWallTile>(XY(pos.x-1, pos.y+mainRoomDimensions.y));
	BuildColumn<WoodWallTile>(XY(pos.x-1, pos.y+mainRoomDimensions.y+1));

	//// Right Wall
	BuildColumn<WoodWallTile>(XY(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y-8));
	BuildColumn<WoodWallTile>(XY(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y-7));
	BuildColumn<WoodWallTile>(XY(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y-6));

	BuildColumn<WoodWallTile>(XY(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y-2));
	BuildColumn<WoodWallTile>(XY(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y-1));
	BuildColumn<WoodWallTile>(XY(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y));
	BuildColumn<WoodWallTile>(XY(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y+1));
	
	//// Bottom Wall
	// Column left
	BuildColumn<WoodWallTile>(XY(pos.x, pos.y+mainRoomDimensions.y+1));
	// Column right
	BuildColumn<WoodWallTile>(XY(pos.x+mainRoomDimensions.x-1, pos.y+mainRoomDimensions.y+1));
	// FrontColumns
	BuildColumn<WoodWallTile>(XY(pos.x+1, pos.y+mainRoomDimensions.y+2));
	BuildColumn<WoodWallTile>(XY(pos.x+4, pos.y+mainRoomDimensions.y+2));
	// Arch
	BuildLine<Tile_Black>(XY(pos.x+2, pos.y+mainRoomDimensions.y), XY(pos.x+3, pos.y+mainRoomDimensions.y), true);
}

// Build a column
template <class T_Wall>
void WorldBuilder::BuildColumn(XY pos, bool solidTop)
{
	// Delegate to create the arch (solidly)
	BuildArchAbove<T_Wall>(pos, true, solidTop);
	// Add the wall below the arch
	AddTileTo<WoodWallTile>(XY(pos.x, pos.y), false);
	
	// TODO: Add corresponding wall type permutations - so that this can dynamically add the bottom tile type
	//AddTileTo<T_Wall>(XY(pos.x, pos.y-1), true);
	//AddTileTo<T_Wall>(XY(pos.x, pos.y), false);

	// Bottom Edge
	//AddTileTo<WoodWallTile_Bottom>(XY(pos.x, pos.y+1), false);
}

// Build an arch over the column
template <class T_Wall>
void WorldBuilder::BuildArchAbove(XY pos, bool solidWall, bool solidTop)
{
	// Black top (wall cut-off)
	if (solidTop) AddTileTo<Tile_Black_Solid>(XY(pos.x, pos.y-2), true);
	else		  AddTileTo<Tile_Black>(XY(pos.x, pos.y-2), true);

	// Wall Below Black
	if (solidWall) AddTileTo<WoodWallTile>(XY(pos.x, pos.y-1), true);
	else		   AddTileTo<WoodWallTile_NotSolid>(XY(pos.x, pos.y-1), true);
}

void WorldBuilder::BuildRoom(XY pos, XY dimensions, bool randomDoorway)
{
	// Draw the border
	XY wd = WORLD_DIMENSIONS;
	bool staysWithinWorld = (pos + dimensions) < wd;

	if (staysWithinWorld)
	{
		BuildBorderedRectangle<StoneFloorTile_LightBrown, WoodWallTile>(pos, dimensions);
		if (randomDoorway) BuildRandomDoorway(pos, dimensions);
	}
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
	BuildRectangle<StoneFloorTile_LightBrown>(doorPos, doorDimensions);
}