#pragma once

#include "WorldBuilder.h"
#include "ShapeBuilder.h"
#include "HouseGenerator.h"
#include "Config.h"
#include "Tiles.h"
#include "Door.h"
#include "NPC.h"
#include "LoadingOutput.h"
#include "ToolKit.h"

using namespace ShapeBuilder;

void WorldBuilder::build()
{
	// Grass World
	LayGrass();

	// Content
	LoadingOutput::Notify(30, "Building Houses");

	//HouseGenerator::Generate();
	BuildHouse_First(Coordinates(WORLD_WIDTH/2-2, WORLD_HEIGHT/2-2));
	//BuildHouse_Realistic1(Coordinates(WORLD_WIDTH/2, WORLD_HEIGHT/2-3));

	// Outer Walls
	LoadingOutput::Notify(5, "Making escape impossible.");

	BuildTileRectangle<WORLD_BORDER>(Coordinates(0, 0), Dimensions(WORLD_WIDTH, WORLD_HEIGHT), false, TOP_LAYER);
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

void WorldBuilder::Erase(const Coordinates& pos, Layer layer)
{
	switch (layer) {
		case TOP_LAYER:	   EraseTop(pos); break;
		case MIDDLE_LAYER: EraseMiddle(pos); break;
		case BOTTOM_LAYER: EraseBottom(pos); break;
	}
}

void WorldBuilder::LayGrass(void)
{
	const int CHANCE_BASE = 10;
	const int CHANCE_CLUSTER = 15;

	bool weedClusters[WORLD_WIDTH][WORLD_HEIGHT];
	int clusterStrengths[WORLD_WIDTH][WORLD_HEIGHT] = {};

	// Lay down the thin grass types everywhere
	int totalLoadingPercentage = 40;

	LoadingOutput::Notify(20, "Laying the grass: 0%");
	for (int i = 0; i < WORLD_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_HEIGHT; j++)
		{
			Coordinates here = Coordinates(i, j);
			int type;		// Used for random determination of grass types of similar kind
			bool occurance; // Use for random choice of tile placement
			
			bool& addClusterHere	 = weedClusters[i][j];
			int& clusterStrength = clusterStrengths[i][j];

			/****** Thin laying (blanket) ******/

			type = rand() % 2;

			// Lay a random type of the two
				 if (type == 0)	AddToBottom<Grass_Thin2_Day>(here);
			else if (type == 1) AddToBottom<Grass_Thin1_Day>(here);
			


			/****** Base grass (sprinkled) ******/

			occurance = (rand() % CHANCE_BASE) == 0;
			if (occurance)
			{
				type = rand() % 2;

				// Lay a random type of the two
					 if (type == 0)	AddToBottom<Grass_Base1_Day>(here);
				else if (type == 1) AddToBottom<Grass_Base2_Day>(here);
			}



			/****** Weed clustering ******/

			// Set whether or not this place has a weed cluster
			addClusterHere = (rand() % CHANCE_CLUSTER) == 0;

			if (addClusterHere) // Determine the strength of the cluster's center
			{
				// Make a non-linear probability distribution, and convert to respective strengths
				int r = rand()%100;

				clusterStrength = 0;

					/* if (r < 15)  clusterStrength = 0;
				else if (r < 45)  clusterStrength = 1;
				else if (r < 85)  clusterStrength = 2;
				else if (r < 100) clusterStrength = 3;*/

					 if (r < 5)   clusterStrength = 0;
				else if (r < 55)  clusterStrength = 1;
				else if (r < 90)  clusterStrength = 2;
				else if (r < 100) clusterStrength = 3;

				//	// if (r < 15)  clusterStrength = 0;
				//if (r < 100)  clusterStrength = 1;
				////else if (r < 85)  clusterStrength = 2;
				////else if (r < 100) clusterStrength = 3;

				//clusterStrength = rand()%4;
			}
		} // End for(j)
	} // End for(i)




	/**** CLUSTERS ****/
	LoadingOutput::Notify(10, "Laying the grass: 50%");

	for (int i = 0; i < WORLD_WIDTH; i++)
	{
		for (int j = 0; j < WORLD_HEIGHT; j++)
		{
			Coordinates here = Coordinates(i, j);
			if (weedClusters[i][j]) // There is a cluster here
			{
				int clusterStrength = clusterStrengths[i][j];
				list<Coordinates> clusterFrontier; // The positions to have clusters added
				list<Coordinates> expendedPositions; // The positions that already have clusters in them

				// Start here
				clusterFrontier.emplace_back(here);

				while (clusterStrength >= 0) // If strength remains
				{
					list<Coordinates> iterationClusters = clusterFrontier;
					for (Coordinates& position : iterationClusters) // For each cluser in the frontier
					{
						// Add a cluster to this position, at this iteration's strength
						AddWeed(clusterStrength, position);

						// Remove this position from the frontier
						clusterFrontier.remove(position);
						// Add it to the expended positions
						expendedPositions.push_front(position); // Add it to the front, to speed future searching


						// Add adjacent, non-visited positions to the frontier for the next iteration
						list<Coordinates> adjacentPositions = Directions<Coordinates>(position).ToList();
						for (Coordinates adjacent : adjacentPositions) // For each adjacent position
						{
							// Ensure in-bounds
							if ((adjacent.x >= 0) && (adjacent.x < WORLD_WIDTH) &&
							    (adjacent.y >= 0) && (adjacent.y < WORLD_HEIGHT))
							{
								if ( !listContains<Coordinates>( expendedPositions, adjacent ) ) // If not expended
									if ( !listContains<Coordinates>( clusterFrontier, adjacent ) ) // If not already added
										clusterFrontier.push_back(adjacent); // Push back, making a copy, of this iteration-scoped element
							}
						}
					}

					// Decrement cluster strength for next iteration
					clusterStrength--;
				}

			}// End if
		}// End for(j)
	}// End for(i)
}

void WorldBuilder::AddWeed(const int strength, const Coordinates& position)
{
		 if (strength == 0) AddToBottom<Grass_Thick1_Day>(position);
	else if (strength == 1) AddToBottom<Grass_Thick2_Day>(position);
	else if (strength == 2) AddToBottom<Grass_Thick3_Day>(position);
	else if (strength == 3) AddToBottom<Grass_Thick4_Day>(position);
	else throw runtime_error("Strength value out of range.");
}


void WorldBuilder::BuildHouse_First(const Coordinates& pos)
{	
	Dimensions mainRoomDimensions(5, 7);
	
	// Main floor
	BuildTileRectangle<StoneFloorTile_LightBrown>(pos, Dimensions(mainRoomDimensions.x, mainRoomDimensions.y+1));
	// Left floor
	BuildTileRectangle<StoneFloorTile>(Coordinates(pos.x-mainRoomDimensions.x+1, pos.y), Dimensions(4, 8));
	// Right floor
	BuildTileRectangle<StoneFloorTile>(Coordinates(pos.x+mainRoomDimensions.x, pos.y), Dimensions(4, 8));
	// Back Entry way floor
	BuildTileRectangle<StoneFloorTile_LightBrown>(Coordinates(pos.x+1, pos.y+mainRoomDimensions.y-9), Dimensions(3, 2));
	// Front Entry way floor
	BuildTileRectangle<StoneFloorTile_LightBrown>(Coordinates(pos.x+1, pos.y+mainRoomDimensions.y+2), Dimensions(3, 2));

	//// LEFT ROOM
	// Back Wall
		BuildLine(Coordinates(pos.x-1, pos.y+mainRoomDimensions.y-8), Coordinates(pos.x-5, pos.y+mainRoomDimensions.y-8), BuildColumn<WoodWallTile>);
	// Left Wall
		BuildLine(Coordinates(pos.x-5, pos.y+mainRoomDimensions.y-7), Coordinates(pos.x-5, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);
	// Front Wall
		BuildLine(Coordinates(pos.x-1, pos.y+mainRoomDimensions.y+1), Coordinates(pos.x-5, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);

	//// RIGHT ROOM
	// Back Wall
		BuildLine(Coordinates(pos.x+6, pos.y+mainRoomDimensions.y-8), Coordinates(pos.x+9, pos.y+mainRoomDimensions.y-8), BuildColumn<WoodWallTile>);
	// Right Wall
		BuildLine(Coordinates(pos.x+9, pos.y+mainRoomDimensions.y-7), Coordinates(pos.x+9, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);
	// Front Wall
		BuildLine(Coordinates(pos.x+6, pos.y+mainRoomDimensions.y+1), Coordinates(pos.x+9, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);

	///////////// MAIN ROOM
	// Back Wall
		//BuildLine(Coordinates(pos.x-1, pos.y+mainRoomDimensions.y-8), Coordinates(pos.x+3, pos.y+mainRoomDimensions.y-8), BuildColumn<WoodWallTile>);
		// Columns left
		BuildColumn<WoodWallTile>(Coordinates(pos.x, pos.y+mainRoomDimensions.y-8));
		BuildColumn<WoodWallTile>(Coordinates(pos.x, pos.y+mainRoomDimensions.y-9));
		// Columns right
		BuildColumn<WoodWallTile>(Coordinates(pos.x+mainRoomDimensions.x-1, pos.y+mainRoomDimensions.y-8));
		BuildColumn<WoodWallTile>(Coordinates(pos.x+mainRoomDimensions.x-1, pos.y+mainRoomDimensions.y-9));
		// Front and Door
		BuildColumn<WoodWallTile>(Coordinates(pos.x, pos.y+mainRoomDimensions.y-10));
		BuildColumn<WoodWallTile>(Coordinates(pos.x+1, pos.y+mainRoomDimensions.y-10));
		BuildDoorColumn(Coordinates(pos.x+2, pos.y+mainRoomDimensions.y-10));
		BuildColumn<WoodWallTile>(Coordinates(pos.x+3, pos.y+mainRoomDimensions.y-10));
		BuildColumn<WoodWallTile>(Coordinates(pos.x+4, pos.y+mainRoomDimensions.y-10));
	
	//// Left Wall
		BuildLine(Coordinates(pos.x-1, pos.y+mainRoomDimensions.y-8), Coordinates(pos.x-1, pos.y+mainRoomDimensions.y-6), BuildColumn<WoodWallTile>);
		BuildLine(Coordinates(pos.x-1, pos.y+mainRoomDimensions.y-2), Coordinates(pos.x-1, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);

	//// Right Wall
		BuildLine(Coordinates(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y-8), Coordinates(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y-6), BuildColumn<WoodWallTile>);
		BuildLine(Coordinates(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y-2), Coordinates(pos.x+mainRoomDimensions.x, pos.y+mainRoomDimensions.y+1), BuildColumn<WoodWallTile>);
	//// NPC
		AddNPC<NPC>(Coordinates(pos.x, pos.y));
		AddNPC<NPC>(Coordinates(pos.x+4, pos.y));
		AddNPC<NPC>(Coordinates(pos.x+4, pos.y+5));
		AddNPC<NPC>(Coordinates(pos.x, pos.y+5));


	//// Bottom Wall
	// Columns left
	BuildColumn<WoodWallTile>(Coordinates(pos.x, pos.y+mainRoomDimensions.y+1));
	BuildColumn<WoodWallTile>(Coordinates(pos.x, pos.y+mainRoomDimensions.y+2));
	// Columns right
	BuildColumn<WoodWallTile>(Coordinates(pos.x+mainRoomDimensions.x-1, pos.y+mainRoomDimensions.y+1));
	BuildColumn<WoodWallTile>(Coordinates(pos.x+mainRoomDimensions.x-1, pos.y+mainRoomDimensions.y+2));
	// Front and Door
	BuildColumn<WoodWallTile>(Coordinates(pos.x, pos.y+mainRoomDimensions.y+3));
	BuildColumn<WoodWallTile>(Coordinates(pos.x+1, pos.y+mainRoomDimensions.y+3));

	BuildColumn<WoodWallTile>(Coordinates(pos.x+2, pos.y+mainRoomDimensions.y+3));
	EraseColumn(Coordinates(pos.x+2, pos.y+mainRoomDimensions.y+3));
	BuildDoorColumn(Coordinates(pos.x+2, pos.y+mainRoomDimensions.y+3));

	BuildColumn<WoodWallTile>(Coordinates(pos.x+3, pos.y+mainRoomDimensions.y+3));
	BuildColumn<WoodWallTile>(Coordinates(pos.x+4, pos.y+mainRoomDimensions.y+3));
}

void WorldBuilder::BuildHouse_Realistic1(const Coordinates& frontDoorPos)
{	
	// Shorthand, used often
	typedef Coordinates C;
	typedef Dimensions D;
	const Coordinates& p = frontDoorPos;
	const float& x = frontDoorPos.x;
	const float& y = frontDoorPos.y;
	Directions<int> doorData = Directions<int>(0, 0, 0, 0);
	HouseGenerator::RoomData data = HouseGenerator::RoomData(0, doorData);
	C origin;

	// Bathroom
	doorData = Directions<int>(-77, 3, -77, -77);
	data = HouseGenerator::RoomData(D(7,8), doorData);
	origin = p + D(-3, -13);
	BuildRoom(origin, data); // Put functionality here until appropriate class is determined

	// !!! Kitchen
	doorData = Directions<int>(-77, -3, -77, -77);
	data = HouseGenerator::RoomData(D(7,10), doorData);
	origin = p + D(3, -15);
	BuildRoom(origin, data); // Put functionality here until appropriate class is determined

	//// Front Room
	//doorData = Directions<int>(3, 3, 4, 3);
	//data = HouseGenerator::RoomData(D(7,9), doorData);
	//origin = p + D(-3, -6);
	//BuildRoom(origin, data); // Put functionality here until appropriate class is determined

	// Garage
	doorData = Directions<int>(-77, -77, -77, 1);
	data = HouseGenerator::RoomData(D(7,8), doorData);
	origin = p + D(-9, -3);
	BuildRoom(origin, data); // Put functionality here until appropriate class is determined
	// Remove the bottom wall
	BuildLine((p + D(-8, 4)), (p + D(-4, 4)), EraseColumn);

	//// Second Room
	//doorData = Directions<int>(-3, -77, 3, 3);
	//data = HouseGenerator::RoomData(D(7,9), doorData);
	//origin = p + D(3, -6);
	//BuildRoom(origin, data); // Put functionality here until appropriate class is determined

	// Living Room
	doorData = Directions<int>(4, -77, 3, -77);
	data = HouseGenerator::RoomData(D(9,9), doorData);
	origin = p + D(9, -6);
	BuildRoom(origin, data); // Put functionality here until appropriate class is determined

	/*
	// Functions
	BuildTileRectangle<StoneFloorTile_LightBrown>(C(x, y), D(5, 5));
	BuildLine(C(x, y), C(x, y), BuildColumn<WoodWallTile>);
	AddNPC<NPC>(C(x, y));
	BuildDoorColumn(C(x, y));
	BuildColumn<WoodWallTile>(C(x, y));
	*/
}

void WorldBuilder::TrustDoorway(const Coordinates& pos)
{
	Erase( Coordinates(pos.x, pos.y-3), TOP_LAYER);
	AddTo<WoodWallTile>( Coordinates(pos.x, pos.y-3), TOP_LAYER);

	Erase( Coordinates(pos.x, pos.y-2), TOP_LAYER);
	Erase( Coordinates(pos.x, pos.y-1), TOP_LAYER);

	Erase(pos, TOP_LAYER);
	Erase(pos, MIDDLE_LAYER);

	Erase( Coordinates(pos.x, pos.y+1), MIDDLE_LAYER);
	Erase( Coordinates(pos.x, pos.y+2), MIDDLE_LAYER);
}

// Build a small column
template <class WallType>
void WorldBuilder::BuildColumn(const Coordinates& pos)
{
	// Replace anything here
	EraseColumn(pos);

	AddTo<TileBlack>(Coordinates(pos.x, pos.y-3), TOP_LAYER);
	AddTo<WallType>(Coordinates(pos.x, pos.y-2), TOP_LAYER);
	AddTo<WallType>(Coordinates(pos.x, pos.y-1), MIDDLE_LAYER);
	AddTo<WallType>(pos, MIDDLE_LAYER);
}

// Erase a column shape
void WorldBuilder::EraseColumn(const Coordinates& pos)
{
	Erase(Coordinates(pos.x, pos.y-3), TOP_LAYER);
	Erase(Coordinates(pos.x, pos.y-2), TOP_LAYER);
	Erase(Coordinates(pos.x, pos.y-1), MIDDLE_LAYER);
	Erase(pos, MIDDLE_LAYER);
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

// Build half a column, above a passage to travel through or add a door
void WorldBuilder::BuildDoorway(const Coordinates& pos) {
	AddTo<TileBlack>(Coordinates(pos.x, pos.y-3), TOP_LAYER);
	AddTo<WoodWallTile>(Coordinates(pos.x, pos.y-2), TOP_LAYER);
	AddTo<WoodWallTile_Above>(Coordinates(pos.x, pos.y-1), MIDDLE_LAYER);
}

// Builds a door with a column above it
void WorldBuilder::BuildDoorColumn(const Coordinates& pos) {
	BuildDoorway(pos);
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

void WorldBuilder::BuildRoom(const Coordinates& origin, const HouseGenerator::RoomData& data)
{
	typedef Coordinates C;
	typedef Dimensions D;

	// Floor
	BuildTileRectangle<StoneFloorTile_LightBrown>(C(origin.x, origin.y+1), D(data.dimensions.x, data.dimensions.y-1));
	// Walls
	ShapeBuilder::BuildRectangle(origin, data.dimensions, BuildColumn<WoodWallTile>, false);
	// NOTE: Add out of bounds checks
	// Doorways
	if (data.doorPositions.top != -77) { // If not code for null
		// Use the polarity to determine the doorway style
		if (data.doorPositions.top > 0)		 ColumnToDoor(    C(origin.x+data.doorPositions.top, origin.y) );
		else if (data.doorPositions.top < 0) ColumnToDoorway( C(origin.x-data.doorPositions.top, origin.y) );
	}
	if (data.doorPositions.bottom != -77) {
		// Use the polarity to determine the doorway style
		if (data.doorPositions.bottom > 0)		ColumnToDoor(    C(origin.x+data.doorPositions.bottom, origin.y+data.dimensions.y-1) );
		else if (data.doorPositions.bottom < 0) ColumnToDoorway( C(origin.x-data.doorPositions.bottom, origin.y+data.dimensions.y-1) );
	}
	if (data.doorPositions.left != -77) {
		TrustDoorway( C(origin.x, origin.y+data.doorPositions.left) );
	}
	if (data.doorPositions.right != -77){
		TrustDoorway( C(origin.x+data.dimensions.x-1, origin.y+data.doorPositions.right) );
	}
}

template <class NPC_Type>
void WorldBuilder::AddNPC(const Coordinates& _pos)
{
	AddTo<NPC_Type>(_pos, MIDDLE_LAYER);
}
