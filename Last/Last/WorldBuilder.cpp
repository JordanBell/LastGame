#pragma once

#include "WorldBuilder.h"
#include "HouseGenerator.h"

using namespace ShapeBuilder;

void WorldBuilder::build()
{
	// Grass World
	BuildTileRectangle<GrassTile>(XY(0, 0), XY(WORLD_WIDTH, WORLD_HEIGHT));

	// Content
	//HouseGenerator::generate();
	BuildTestHouse(XY(WORLD_WIDTH/2-3, WORLD_HEIGHT/2-4));

	// Outer Walls
	BuildTileRectangle<WORLD_BORDER>(XY(0, 0), XY(WORLD_WIDTH, WORLD_HEIGHT), false, true);
}

template <class T>
void WorldBuilder::AddTileTo(const XY& pos, const bool top, const bool reverseSolidarity)
{
	// Create an object of that tile type
	T* tile = new T(pos.x, pos.y);
	if (reverseSolidarity) tile->Tile::canMoveThrough = !tile->Tile::canMoveThrough; // Reverse it, if set to do so

	// Add the tile to the specified layer
	if (top) g_environment->AddTileToTop(tile);
	else	 g_environment->AddTileToBottom(tile);
}

void WorldBuilder::BuildTestHouse(const XY& pos)
{	
	XY mainRoomDimensions(6, 7);
	
	// Main floor
	BuildTileRectangle<StoneFloorTile_LightBrown>(pos, XY(mainRoomDimensions.x, mainRoomDimensions.y+1));
	// Left floor
	BuildTileRectangle<StoneFloorTile>(XY(pos.x-mainRoomDimensions.x+2, pos.y), XY(4, 8));
	// Right floor
	BuildTileRectangle<StoneFloorTile>(XY(pos.x+mainRoomDimensions.x, pos.y), XY(4, 8));
	// Entry way floor
	BuildTileRectangle<StoneFloorTile_LightBrown>(XY(pos.x+1, pos.y+mainRoomDimensions.y+2), XY(4, 2));

	//// LEFT ROOM
	// Back Wall
		BuildLine(XY(pos.x-2, pos.y+mainRoomDimensions.y-8), XY(pos.x-5, pos.y+mainRoomDimensions.y-8), BuildColumn<WoodWallTile>);
	// Left Wall
		BuildLine(XY(pos.x-5, pos.y+mainRoomDimensions.y-7), XY(pos.x-5, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);
	// Front Wall
		BuildLine(XY(pos.x-2, pos.y+mainRoomDimensions.y+1), XY(pos.x-5, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);

	//// RIGHT ROOM
	// Back Wall
		BuildLine(XY(pos.x+7, pos.y+mainRoomDimensions.y-8), XY(pos.x+10, pos.y+mainRoomDimensions.y-8), BuildColumn<WoodWallTile>);
	// Right Wall
		BuildLine(XY(pos.x+10, pos.y+mainRoomDimensions.y-7), XY(pos.x+10, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);
	// Front Wall
		BuildLine(XY(pos.x+7, pos.y+mainRoomDimensions.y+1), XY(pos.x+10, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);

	///////////// MAIN ROOM
	// Back Wall
		BuildLine(XY(pos.x-1, pos.y+mainRoomDimensions.y-8), XY(pos.x+6, pos.y+mainRoomDimensions.y-8), BuildColumn<WoodWallTile>);
	
	//// Left Wall
		BuildLine(XY(pos.x-1, pos.y+mainRoomDimensions.y-8), XY(pos.x-1, pos.y+mainRoomDimensions.y-6), BuildColumn<WoodWallTile>);
		BuildLine(XY(pos.x-1, pos.y+mainRoomDimensions.y-2), XY(pos.x-1, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);

	//// Right Wall
		BuildLine(XY(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y-8), XY(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y-6), BuildColumn<WoodWallTile>);
		BuildLine(XY(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y-2), XY(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);
	
	//// Bottom Wall
	// Column left
	BuildColumn<WoodWallTile>(XY(pos.x, pos.y+mainRoomDimensions.y+2));
	// Column right
	BuildColumn<WoodWallTile>(XY(pos.x+mainRoomDimensions.x-1, pos.y+mainRoomDimensions.y+2));
	// FrontColumns
	BuildColumn<WoodWallTile>(XY(pos.x+1, pos.y+mainRoomDimensions.y+3));
	BuildColumn<WoodWallTile>(XY(pos.x+4, pos.y+mainRoomDimensions.y+3));
	// Arch
	BuildColumn<WoodWallTile>(XY(pos.x+2, pos.y+mainRoomDimensions.y+3));
	BuildDoorColumn(XY(pos.x+3, pos.y+mainRoomDimensions.y+3));
}

// Build a small column
template <class T_Wall>
void WorldBuilder::BuildColumn(const XY& pos)
{
	AddTileTo<Tile_Black>(XY(pos.x, pos.y-2), true);	// Black
	AddTileTo<WoodWallTile>(XY(pos.x, pos.y-1));		// Wall
	AddTileTo<WoodWallTile>(pos);						// Wall
}

// Build a column
template <class T_Wall>
void WorldBuilder::BuildColumnLarge(const XY& pos)
{
	// Delegate to create the arch (solidly)
	BuildColumn<T_Wall>(XY(pos.x, pos.y-1));
	// Add the wall below the arch
	AddTileTo<WoodWallTile>(pos);
}

// Build an arch over a position
template <class T_Wall>
void WorldBuilder::BuildArchAbove(const XY& pos)
{
	AddTileTo<Tile_Black>(XY(pos.x, pos.y-2), true);			// Black
	AddTileTo<WoodWallTile>(XY(pos.x, pos.y-1), true, true);	// Wall
}

// Build an arch over a position
void WorldBuilder::BuildDoorColumn(const XY& pos)
{
	AddTileTo<Tile_Black>(XY(pos.x, pos.y-2), true);			// Black
	AddTileTo<WoodWallTile_Half>(XY(pos.x, pos.y-1), true);	// Wall Half
	AddTileTo<Door>(pos);
}

void WorldBuilder::BuildRoom(const XY& pos, const XY& dimensions)
{
	// Draw the border
	const bool staysWithinWorld = (pos + dimensions) < WORLD_DIMENSIONS;

	if (staysWithinWorld)
	{
		BuildTileRectangle<StoneFloorTile_LightBrown>(pos, dimensions);
		BuildRectangle(pos, dimensions, BuildColumn<WoodWallTile>, false);

		// TopDown, primitive style
		/*BuildBorderedRectangle<StoneFloorTile_LightBrown, WoodWallTile>(pos, dimensions);
		BuildRandomDoorway(pos, dimensions);*/
	}
}

// Deprecated upon implementation of uniplanar isometric houses
void WorldBuilder::BuildRandomDoorway(const XY& pos, const XY& dimensions)
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
	BuildTileRectangle<StoneFloorTile_LightBrown>(doorPos, doorDimensions);
}