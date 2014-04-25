#pragma once
#pragma warning(disable: 4715)
#include "HouseGenerator.h"
#include "WorldBuilder.h"
#include "Environment.h"
#include <stdlib.h>

void HouseGenerator::run(void)
{
	// Warning: Not a very smart calculation on the number of houses allowed on the screen.
	XY world = WORLD_DIMENSIONS;
	XY maxHouseDimensions = (LARGE.dimensions * (float)(1 + (1.6*HOUSE_SIZE_DEVIATION)));

	XY numHouses = world / maxHouseDimensions;
	numHouses.x = (int)numHouses.x;
	numHouses.y = (int)numHouses.y;

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
				WorldBuilder::BuildRoom(position, dimensions, true);

				// Extra: Add a small room to the center of large houses
				if (size.numRooms == 3) WorldBuilder::BuildRoom(position + dimensions/4, dimensions/2, true);
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
}




//#pragma once
//#include "HouseGenerator.h"
//#include "Environment.h"
//#include <stdlib.h>
//
//void HouseGenerator::run(void)
//{
//	// Warning: Not a very smart calculation on the number of houses allowed on the screen.
//	XY numHouses = XY(
//		WORLD_WIDTH  / (LARGE.w + 5),
//		WORLD_HEIGHT / (LARGE.h + 5)); 
//
//	for (int i = 0; i < numHouses.x; i++)
//	{
//		for (int j = 0; j < numHouses.y; j++)
//		{
//			HouseSize size = ComputeRandomSize();
//			XY* position = new XY(
//				(i * LARGE.w*(1+HOUSE_SIZE_DEVIATION)) +5, 
//				(j * LARGE.h*(1+HOUSE_SIZE_DEVIATION)) +5);
//			
//			//for (int k = 0; k < size.numRooms; k++)
//			for (int k = 0; k < 1; k++)
//			{
//				// Build a room
//				// The width and height ranges of size, based on the size w and h, and the global size deviation percentage
//				XY range(
//					HOUSE_SIZE_DEVIATION*2 * size.w, 
//					HOUSE_SIZE_DEVIATION*2 * size.h);
//
//				// Find random numbers within that range, with a median at 0
//				XY sizeDeviation(
//					(rand() % (int)range.x) - range.x/2, 
//					(rand() % (int)range.y) - range.y/2);
//
//				int width = size.w + sizeDeviation.x;
//				int height = size.h + sizeDeviation.y;
//
//				// Build the room with a random door (for now... random doors can't work with connected rooms... yet)
//				g_environment->BuildRoom(position->x, position->y, width, height, true);
//
//				if (size.numRooms == 3) g_environment->BuildRoom(position->x + width/4, position->y + height/4, width/2, height/2, true);
//			}
//		}
//	}
//}
//
//HouseGenerator::HouseSize HouseGenerator::ComputeRandomSize(void)
//{
//	int size = rand() % 3;
//	switch (size)
//	{
//		case 0: return SMALL;
//		case 1: return MEDIUM;
//		case 2: return LARGE;
//	}
//
//	return LARGE;
//}
//
//
//
//
//#include "Environment.h"
//#include "Resources.h"
//#include "HouseGenerator.h"
//#include "Game.h"
//
//Environment* g_environment = NULL;
//
//Environment::Environment(float x, float y) : EntityContainer(x, y) 
//{
//	// Default tiles (grass, surrounded by a wall so that the player can't escape)
//	BuildBorderedRectangle<GrassTile, WORLD_BORDER>(0, 0, WORLD_WIDTH, WORLD_HEIGHT);
//}
//
//void Environment::BuildMap()
//{
//	HouseGenerator hg = HouseGenerator();
//	hg.run();
//
//	// Manually build a little house and grand exit hallway
//	//BuildRoom(4, 3, 12, 8);
//	//BuildRoom(8, 10, 4, 8);
//	//BuildRectangle<StoneFloorTile>(9, 10, 2, 1); // A doorway
//	//BuildRectangle<StoneFloorTile>(9, 17, 2, 1); // A doorway
//}
//
//// Try to center the environment on the player, if this would not overstep the edges
//void Environment::centerOn(Player* player)
//{
//	// Check to see where this would center to
//	XY distFromCenter = XY(player->x - SCREEN_CENTER.x,
//						   player->y - SCREEN_CENTER.y);
//
//	int suggestedX = x - distFromCenter.x;
//	int suggestedY = y - distFromCenter.y;
//
//	// Only center it if those coordinates are within the edges (Make x and y centering independant)
//	Directions<bool> xBools = GetEdgeBools(suggestedX, 0);
//	Directions<bool> yBools = GetEdgeBools(0, suggestedY);
//
//	if (!xBools.left && !xBools.right)
//	{
//		//printf("Moving X\n");
//		g_game->MoveEverything(-distFromCenter.x, 0);
//	}
//
//	if (!yBools.top && !yBools.bottom)
//	{
//		//printf("Moving Y\n");
//		g_game->MoveEverything(0, -distFromCenter.y);
//	}
//
//	// Snap everything real nice.
//	player->SnapPosition();
//}
//
//Directions<bool> Environment::GetEdgeBools()
//{
//	return GetEdgeBools(x, y);
//}
//
//Directions<bool> Environment::GetEdgeBools(float _x, float _y)
//{
//	Directions<bool> r_directions = Directions<bool>(
//		(int)_y >= 0,
//		(int)_y <= SCREEN_HEIGHT - WORLD_HEIGHT * TILE_SIZE,
//		(int)_x >= 0,
//		(int)_x <= SCREEN_WIDTH  - WORLD_WIDTH * TILE_SIZE);
//
//	return r_directions;
//}
//
//GridTile* Environment::getTileAt(XY* gridPosition)
//{
//	return tiles[(int)gridPosition->x][(int)gridPosition->y];
//}
//
//void Environment::BuildRoom(int x, int y, int w, int h, bool randomDoorway)
//{
//	// Draw the border
//	BuildBorderedRectangle<StoneFloorTile, StoneWallTile>(x, y, w, h);
//
//	if (randomDoorway)
//	{
//		// Find where along the wall the doorway should go
//		XY* doorPos = new XY(0, 0);
//		bool isOnSides = rand() % 2;
//
//		if (isOnSides) 
//		{
//			doorPos->y = y + (rand() % (h-3)) + 1;
//			
//			bool left = rand() % 2;
//			doorPos->x = left ? x : x+w-1;
//		}
//		else
//		{
//			doorPos->x = x + (rand() % (w-3)) + 1;
//			
//			bool top = rand() % 2;
//			doorPos->y = top ? y : y+h-1;
//		}
//		
//		// Build the door
//		BuildRectangle<StoneFloorTile>(doorPos->x, doorPos->y, isOnSides? 1 : 2, isOnSides? 2 : 1);
//	}
//}
//
//template <class T_Fill, class T_Border>
////template <class T_Border>
//void Environment::BuildBorderedRectangle(int x, int y, int w, int h)
//{
//	// Draw the border
//	BuildRectangle<T_Border>(x, y, w, h, false);
//	// Draw the fill
//	BuildRectangle<T_Fill>(x+1, y+1, w-2, h-2, true);
//}
//
//template <class T>
//void Environment::BuildRectangle(int x, int y, int w, int h, bool filled)
//{
//	for (int i = x; i < x+w; i++)
//	{
//		for (int j = y; j < y+h; j++)
//		{
//			if (filled) AddTileTo<T>(i, j);
//			else
//			{
//				bool xEdge = ((i == x) || (i == x+w-1));
//				bool yEdge = ((j == y) || (j == y+h-1));
//				if (xEdge || yEdge) AddTileTo<T>(i, j);
//			}
//		}
//	}
//}
//
//template <class T>
//void Environment::AddTileTo(int _x, int _y)
//{
//	T* tile = new T(_x, _y);
//	tiles[_x][_y] = tile;
//	addChild(tile);
//}