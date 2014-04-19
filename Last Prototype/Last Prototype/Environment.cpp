#include "Environment.h"
#include "Resources.h"

Environment* g_environment = NULL;

Environment::Environment(float x, float y) : EntityContainer(x, y)
{
	BuildMap();
}

GridTile* Environment::getTileAt(XY* gridPosition)
{
	return tiles[(int)gridPosition->x][(int)gridPosition->y];
}

void Environment::BuildMap()
{
	// Default tiles (grass, surrounded by a wall so that the player can't escape)
	BuildBorderedRectangle<GrassTile, InvisibleWallTile>(0, 0, WORLD_WIDTH, WORLD_HEIGHT);

	// Build a little house
	BuildBorderedRectangle<StoneFloorTile, StoneWallTile>(4, 3, 12, 8);
	BuildRectangle<StoneFloorTile>(9, 10, 2, 1); // The Doorway
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