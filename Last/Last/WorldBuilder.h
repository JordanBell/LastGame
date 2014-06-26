#pragma once
#include "Tools.h"
#include "ToolKit.h"
#include "Environment.h"

#define WORLD_BORDER ShinyBlockTile

class WorldBuilder
{
friend class Room;
public:
	// Run the WorldBuilder code
	static void build(void);

	// Add a type of Entity to the environment on a specified layer
	template <class E>
		static void AddTo(const Coordinates& pos, Layer layer = BOTTOM_LAYER);
	// Add an Entity to a top position
	template <class E>
		static void AddToTop(const Coordinates& pos) { g_environment->AddToTop(new E(pos)); }
	// Add an Entity to a bottom position
	template <class E>
		static void AddToMiddle(const Coordinates& pos) { g_environment->AddToMiddle(new E(pos)); }
	// Add an Entity to a bottom position
	template <class E>
		static void AddToBottom(const Coordinates& pos) { g_environment->AddToBottom(new E(pos)); }

private:

	// Build a test house
	static void BuildTestHouse(const Coordinates& pos);

	// Build a stone bordered square - not a real room, really.
	static void BuildRoom(const Coordinates& pos, const XY& dimensions);

	static void LayGrass(void);
	static void AddWeed(const int strength, const Coordinates& position);

	// Build a small column
	template <class T_Wall>
		static void BuildColumn(const Coordinates& pos);

	// Build a column of walls, topped with an optionally solid Black.
	template <class T_Wall>
		static void BuildColumnLarge(const Coordinates& pos);

	// Builds a door with a column above it
	static void BuildDoorColumn(const Coordinates& pos);

	// Add an NPC to the world
	template <class NPC_Type>
		static void AddNPC(const Coordinates& _pos);
};