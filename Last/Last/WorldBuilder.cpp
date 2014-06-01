#pragma once

#include "WorldBuilder.h"
#include "ShapeBuilder.h"
#include "HouseGenerator.h"
#include "Config.h"
#include "Tiles.h"
#include "Door.h"
#include "NPC.h"

using namespace ShapeBuilder;

void WorldBuilder::build()
{
	// Grass World
	BuildTileRectangle<GrassTile>(Coordinates(0, 0), Dimensions(WORLD_WIDTH, WORLD_HEIGHT));

	// Content
	//HouseGenerator::Generate();
	BuildTestHouse(Coordinates(WORLD_WIDTH/2-3, WORLD_HEIGHT/2-4));

	AddToMiddle<NPC>(Coordinates(WORLD_WIDTH/2-1, WORLD_HEIGHT/2));

	// Outer Walls
	BuildTileRectangle<InvisibleWallTile>(Coordinates(0, 0), Dimensions(WORLD_WIDTH, WORLD_HEIGHT), false, TOP_LAYER);
}

template <class E>
void WorldBuilder::AddTo(const Coordinates& pos, Layer layer)
{
	switch (layer) {
		case TOP_LAYER:	   AddToTop<E>(pos); break;
		case MIDDLE_LAYER: AddToMiddle<E>(pos); break;
		case BOTTOM_LAYER: AddToBottom<E>(pos); break;
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
	//// NPC
		AddNPC<NPC>(Coordinates(pos.x+2, pos.y+4));
		/*AddNPC<NPC>(Coordinates(pos.x+4, pos.y+5));
		AddNPC<NPC>(Coordinates(pos.x+1, pos.y+4));
		AddNPC<NPC>(Coordinates(pos.x+2, pos.y+3));*/


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
template <class WallType>
void WorldBuilder::BuildColumn(const Coordinates& pos)
{
	AddTo<TileBlack>(Coordinates(pos.x, pos.y-2), TOP_LAYER);
	AddTo<WallType>(Coordinates(pos.x, pos.y-1));
	AddTo<WallType>(pos);
}

// Build a column
template <class WallType>
void WorldBuilder::BuildColumnLarge(const Coordinates& pos)
{
	// Delegate to create the arch (solidly)
	BuildColumn<WallType>(Coordinates(pos.x, pos.y-1));
	// Add the wall below the arch
	AddTo<WallType>(pos);
}

// Build an arch over a position
void WorldBuilder::BuildDoorColumn(const Coordinates& pos)
{
	AddTo<TileBlack>(Coordinates(pos.x, pos.y-2), TOP_LAYER);
	AddTo<WoodWallTile_Above>(Coordinates(pos.x, pos.y-1), TOP_LAYER);
	AddTo<Door>(pos, MIDDLE_LAYER);
}

void WorldBuilder::BuildRoom(const Coordinates& pos, const Dimensions& dimensions)
{
	// Draw the border
	const bool staysWithinWorld = (pos + dimensions) < WORLD_DIMENSIONS;

	if (staysWithinWorld)
	{
		BuildTileRectangle<StoneFloorTile_LightBrown>(pos, dimensions);
		BuildRectangle(pos, dimensions, BuildColumn<WoodWallTile>, false);
	}
}

template <class NPC_Type>
void WorldBuilder::AddNPC(const Coordinates& _pos)
{
	AddTo<NPC_Type>(_pos, MIDDLE_LAYER);
}
