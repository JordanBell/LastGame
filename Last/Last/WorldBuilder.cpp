#pragma once

#include "WorldBuilder.h"
#include "ShapeBuilder.h"
#include "Config.h"
#include "Tiles.h"
#include "Door.h"

using namespace ShapeBuilder;

void WorldBuilder::build()
{
	// Grass World
	BuildTileRectangle<GrassTile>(Coordinates(0, 0), Dimensions(WORLD_WIDTH, WORLD_HEIGHT));

	// Content
	//HouseGenerator::generate();
	//BuildTestHouse(Coordinates(WORLD_WIDTH/2-3, WORLD_HEIGHT/2-4));

	// Outer Walls
	BuildTileRectangle<WORLD_BORDER>(Coordinates(0, 0), Dimensions(WORLD_WIDTH, WORLD_HEIGHT), false, TOP_LAYER);
}

template <class E>
void WorldBuilder::AddTo(const Coordinates& pos, Layer layer)
{
	switch (layer) {
		case TOP_LAYER: AddToTop<E>(pos);
		case MIDDLE_LAYER: AddToMiddle<E>(pos);
		case BOTTOM_LAYER: AddToBottom<E>(pos);
	}
}

void WorldBuilder::BuildTestHouse(const Coordinates& pos)
{	
	Dimensions mainRoomDimensions(6, 7);
	
	// Main floor
	BuildTileRectangle<StoneFloorTile_LightBrown>(pos, Dimensions(mainRoomDimensions.x, mainRoomDimensions.y+1));
	// Left floor
	BuildTileRectangle<StoneFloorTile>(Coordinates(pos.x-mainRoomDimensions.x+2, pos.y), Dimensions(4, 8));
	// Right floor
	BuildTileRectangle<StoneFloorTile>(Coordinates(pos.x+mainRoomDimensions.x, pos.y), Dimensions(4, 8));
	// Entry way floor
	BuildTileRectangle<StoneFloorTile_LightBrown>(Coordinates(pos.x+1, pos.y+mainRoomDimensions.y+2), Dimensions(4, 2));

	//// LEFT ROOM
	// Back Wall
		BuildLine(Coordinates(pos.x-2, pos.y+mainRoomDimensions.y-8), Dimensions(pos.x-5, pos.y+mainRoomDimensions.y-8), BuildColumn<WoodWallTile>);
	// Left Wall
		BuildLine(Coordinates(pos.x-5, pos.y+mainRoomDimensions.y-7), Dimensions(pos.x-5, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);
	// Front Wall
		BuildLine(Coordinates(pos.x-2, pos.y+mainRoomDimensions.y+1), Dimensions(pos.x-5, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);

	//// RIGHT ROOM
	// Back Wall
		BuildLine(Coordinates(pos.x+7, pos.y+mainRoomDimensions.y-8), Dimensions(pos.x+10, pos.y+mainRoomDimensions.y-8), BuildColumn<WoodWallTile>);
	// Right Wall
		BuildLine(Coordinates(pos.x+10, pos.y+mainRoomDimensions.y-7), Dimensions(pos.x+10, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);
	// Front Wall
		BuildLine(Coordinates(pos.x+7, pos.y+mainRoomDimensions.y+1), Dimensions(pos.x+10, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);

	///////////// MAIN ROOM
	// Back Wall
		BuildLine(Coordinates(pos.x-1, pos.y+mainRoomDimensions.y-8), Dimensions(pos.x+6, pos.y+mainRoomDimensions.y-8), BuildColumn<WoodWallTile>);
	
	//// Left Wall
		BuildLine(Coordinates(pos.x-1, pos.y+mainRoomDimensions.y-8), Dimensions(pos.x-1, pos.y+mainRoomDimensions.y-6), BuildColumn<WoodWallTile>);
		BuildLine(Coordinates(pos.x-1, pos.y+mainRoomDimensions.y-2), Dimensions(pos.x-1, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);

	//// Right Wall
		BuildLine(Coordinates(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y-8), Dimensions(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y-6), BuildColumn<WoodWallTile>);
		BuildLine(Coordinates(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y-2), Dimensions(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);
	
	//// Bottom Wall
	// Column left
	BuildColumn<WoodWallTile>(Coordinates(pos.x, pos.y+mainRoomDimensions.y+2));
	// Column right
	BuildColumn<WoodWallTile>(Coordinates(pos.x+mainRoomDimensions.x-1, pos.y+mainRoomDimensions.y+2));
	// FrontColumns
	BuildColumn<WoodWallTile>(Coordinates(pos.x+1, pos.y+mainRoomDimensions.y+3));
	BuildColumn<WoodWallTile>(Coordinates(pos.x+4, pos.y+mainRoomDimensions.y+3));
	// Arch
	BuildColumn<WoodWallTile>(Coordinates(pos.x+2, pos.y+mainRoomDimensions.y+3));
	BuildDoorColumn(Coordinates(pos.x+3, pos.y+mainRoomDimensions.y+3));
}

// Build a small column
template <class Wall>
void WorldBuilder::BuildColumn(const Coordinates& pos)
{
	AddTo<TileBlack>(Coordinates(pos.x, pos.y-2), TOP_LAYER);
	AddTo<WoodWallTile>(Coordinates(pos.x, pos.y-1));
	AddTo<WoodWallTile>(pos);
}

// Build a column
template <class Wall>
void WorldBuilder::BuildColumnLarge(const Coordinates& pos)
{
	// Delegate to create the arch (solidly)
	BuildColumn<Wall>(Coordinates(pos.x, pos.y-1));
	// Add the wall below the arch
	AddTo<WoodWallTile>(pos);
}

// Build an arch over a position
template <class Wall>
void WorldBuilder::BuildArchAbove(const Coordinates& pos)
{
	AddTo<TileBlack>(Coordinates(pos.x, pos.y-2), true);			// Black
	AddTo<WoodWallTile>(Coordinates(pos.x, pos.y-1), TOP_LAYER);	// Wall
}

// Build an arch over a position
void WorldBuilder::BuildDoorColumn(const Coordinates& pos)
{
	AddTo<TileBlack>(Coordinates(pos.x, pos.y-2), TOP_LAYER);			// Black
	AddTo<WoodWallTile_Half>(Coordinates(pos.x, pos.y-1), TOP_LAYER);	// Wall Half
	AddTo<Door>(pos);													// Door
}

void WorldBuilder::BuildRoom(const Coordinates& pos, const Dimensions& dimensions)
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
void WorldBuilder::BuildRandomDoorway(const Coordinates& pos, const Dimensions& dimensions)
{
	// Find where along the wall the doorway should go
	Coordinates doorPos = Coordinates(0, 0);
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
	Dimensions doorDimensions = Dimensions(isOnHorizontal? 1 : 2,
							isOnHorizontal? 2 : 1);
		
	// Build the door
	BuildTileRectangle<StoneFloorTile_LightBrown>(doorPos, doorDimensions);
}