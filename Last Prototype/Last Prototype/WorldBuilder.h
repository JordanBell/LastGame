#pragma once
#include "Environment.h"
#include "HouseGenerator.h"
#include "ShapeBuilder.h"

#define WORLD_BORDER ShinyBlockTile

class WorldBuilder
{
friend class HouseGenerator;
public:
	// Run the WorldBuilder code
	static void build(void);

	// Add a type of tile to the environment on a specified layer
	template <class T>
		static void AddTileTo(XY pos, bool top = false, bool reverseSolidarity = false);

private:

	////// STRUCTURES

	// Build a test house
	static void BuildTestHouse(XY pos);

	// Build a column of walls, topped with an optionally solid Black.
	template <class T_Wall>
		static void BuildColumn(XY pos, bool solidTop = false);

	// An arch above a certain point - a wall and an optionally solid black
	template <class T_Wall>
		static void BuildArchAbove(XY pos, bool solidWall = false, bool solidTop = false);

	// Build a stone bordered square with optional random doorway
	static void BuildRoom(XY pos, XY dimensions, bool randomDoorway = false);

	// Build a random doorway along a given square
	static void BuildRandomDoorway(XY pos, XY dimensions);
};