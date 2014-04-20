#include "Environment.h"
#include "Resources.h"
#include "HouseGenerator.h"
// NOTE NOTE NOTE NOTE NOTE Does this line need to be here? Check once there aren't so many unknowns as to what's causing any problems.
Environment* g_environment = NULL;

Environment::Environment(float x, float y) : EntityContainer(x, y) 
{
	// Default tiles (grass, surrounded by a wall so that the player can't escape)
	BuildBorderedRectangle<GrassTile, WORLD_BORDER>(0, 0, WORLD_WIDTH, WORLD_HEIGHT);
}

void Environment::BuildMap()
{
	// Manually build a little house and grand exit hallway
	BuildRoom(4, 3, 12, 8);
	BuildRoom(8, 10, 4, 8);
	BuildRectangle<StoneFloorTile>(9, 10, 2, 1); // A doorway
	BuildRectangle<StoneFloorTile>(9, 17, 2, 1); // A doorway
}

void Environment::generate(void)
{
	HouseGenerator hg = HouseGenerator();
	hg.run();
}

GridTile* Environment::getTileAt(XY* gridPosition)
{
	return tiles[(int)gridPosition->x][(int)gridPosition->y];
}

void Environment::BuildRoom(int x, int y, int w, int h, bool randomDoorway)
{
	// Draw the border
	BuildBorderedRectangle<StoneFloorTile, StoneWallTile>(x, y, w, h);

	if (randomDoorway)
	{
		// Find where along the wall the doorway should go
		XY* doorPos = new XY(0, 0);
		bool isOnSides = rand() % 2;

		if (isOnSides) 
		{
			doorPos->y = y + (rand() % (h-2));
			
			bool left = rand() % 2;
			doorPos->x = left ? x : x+w-1;
		}
		else
		{
			doorPos->x = x + (rand() % (w-2));
			
			bool top = rand() % 2;
			doorPos->y = top ? y : y+h-1;
		}
		
		// Build the door
		BuildRectangle<StoneFloorTile>(doorPos->x, doorPos->y, isOnSides? 1 : 2, isOnSides? 2 : 1);
	}
}

template <class T_Fill, class T_Border>
//template <class T_Border>
void Environment::BuildBorderedRectangle(int x, int y, int w, int h)
{
	// Draw the border
	BuildRectangle<T_Border>(x, y, w, h, false);
	// Draw the fill
	BuildRectangle<T_Fill>(x+1, y+1, w-2, h-2, true);
}

template <class T>
void Environment::BuildRectangle(int x, int y, int w, int h, bool filled)
{
	for (int i = x; i < x+w; i++)
	{
		for (int j = y; j < y+h; j++)
		{
			if (filled) AddTileTo<T>(i, j);
			else
			{
				bool xEdge = ((i == x) || (i == x+w-1));
				bool yEdge = ((j == y) || (j == y+h-1));
				if (xEdge || yEdge) AddTileTo<T>(i, j);
			}
		}
	}
}

template <class T>
void Environment::AddTileTo(int _x, int _y)
{
	T* tile = new T(_x, _y);
	tiles[_x][_y] = tile;
	addChild(tile);
}