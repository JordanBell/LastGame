#ifndef environment_h
#define environment_h
#pragma once

#include "EntityContainer.h"
#include "GridTiles.h"
#include "Config.h"
#include "Tools.h"

class Environment :
	public EntityContainer
{
public:
	Environment(float x, float y);
	~Environment(void);

	void update(int delta) {}
	GridTile* getTileAt(XY* gridPosition);

private:
	int width, height; //The total size of the world
	GridTile* tiles[WORLD_WIDTH][WORLD_HEIGHT]; // Note: Make 2D array of lists of tiles; Tile Layer? Used if a position has several tiles on top, and we don't want to override any tiles in that position.

	void BuildMap(void);

	template <class T_Fill, class T_Border>
	//template <class T_Border>
	void BuildBorderedRectangle(int x, int y, int w, int h);

	template <class T>
	void BuildRectangle(int x, int y, int w, int h, bool filled = true);
	template <class T>
	void AddTileTo(int _x, int _y);
};

extern Environment* g_environment;

#endif