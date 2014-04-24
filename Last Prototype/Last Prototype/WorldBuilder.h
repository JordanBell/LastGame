#pragma once
#include "Environment.h"

class WorldBuilder
{
public:
	// Run the WorldBuilder code
	static void build(void);

	// Build a stone bordered square with optional random doorway
	static void BuildRoom(XY pos, XY dimensions, bool randomDoorway = false);

private:
	// Build a random doorway along a given square
	static void BuildRandomDoorway(XY pos, XY dimensions);

	// Build a rectangle with a border, setting different GridTiles as the fill and border
	template <class T_Fill, class T_Border>
		static void BuildBorderedRectangle(XY pos, XY dimensions);

	// Build a rectangle with a border, setting different GridTiles as the fill and border
	template <class T>
		static void BuildRectangle(XY pos, XY dimensions, bool filled = true);
		
	// Add a tile of a certain type to the environment
	template <class T>
		static void AddTileTo(XY pos);
};

