#pragma once
#include "Environment.h"
#include "HouseGenerator.h"
#include "ShapeBuilder.h"
#include "Room.h"

#define WORLD_BORDER ShinyBlockTile

class WorldBuilder
{
friend class Room;
public:
	// Run the WorldBuilder code
	static void build(void);

	// Add a type of tile to the environment on a specified layer
	template <class T>
		static void AddTileTo(const XY& pos, bool top = false, bool reverseSolidarity = false);
	// Add a tile to a bottom position
	template <class T>
		static void AddTileToBottom(const XY& pos) { AddTileTo<T>(pos, false); }
	// Add a tile to a bottom position
	template <class T>
		static void AddTileToTop(const XY& pos) { AddTileTo<T>(pos, true); }

private:

	////// STRUCTURES

	// Build a test house
	static void BuildTestHouse(const XY& pos);

	// Build a stone bordered square
	static void BuildRoom(const XY& pos, const XY& dimensions);

	// Build a small column
	template <class T_Wall>
		static void BuildColumn(const XY& pos);

	// Build a column of walls, topped with an optionally solid Black.
	template <class T_Wall>
		static void BuildColumnLarge(const XY& pos);

	// An arch above a certain point - a wall and an optionally solid black
	template <class T_Wall>
		static void BuildArchAbove(const XY& pos);

	// Builds a door with a column above it
	static void BuildDoorColumn(const XY& pos);

	// Build a random doorway along a given square
	static void BuildRandomDoorway(const XY& pos, const XY& dimensions);
};