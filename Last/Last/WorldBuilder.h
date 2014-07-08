#pragma once
#include "Tools.h"
#include "ToolKit.h"
#include "Environment.h"
#include "HouseGenerator.h"

#define WORLD_BORDER InvisibleWallTile

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

	// Erasing all tiles at a given position and layer
	static void Erase(const Coordinates& pos, Layer layer = BOTTOM_LAYER);
		static void EraseTop(const Coordinates& pos)	{ g_environment->EraseTop(pos); }
		static void EraseMiddle(const Coordinates& pos) { g_environment->EraseMiddle(pos); }
		static void EraseBottom(const Coordinates& pos) { g_environment->EraseBottom(pos); }
		static void EraseAll(const Coordinates& pos)	{ EraseBottom(pos); EraseMiddle(pos); EraseTop(pos); }

private:

	// Build test houses
	static void BuildHouse_First(const Coordinates& pos);
	static void BuildHouse_Realistic1(const Coordinates& frontDoorPos);

	// Build a stone bordered square - not a real room, really.
	static void BuildRoom(const Coordinates& pos, const Dimensions& dimensions);

	// Build a better room with better data
	static void BuildRoom(const Coordinates& origin, const HouseGenerator::RoomData& data);

	static void LayGrass(void);
	static void AddWeed(const int strength, const Coordinates& position);

	// Erase a column shape above a position
	static void EraseColumn(const Coordinates& pos);

	// Build a small column
	template <class T_Wall>
		static void BuildColumn(const Coordinates& pos);

	// Build a column of walls, topped with an optionally solid Black.
	template <class T_Wall>
		static void BuildColumnLarge(const Coordinates& pos);

	// Build half a column, above a passage to travel through or add a door
	static void BuildDoorway(const Coordinates& pos);

	// Builds a door with a column above it
	static void BuildDoorColumn(const Coordinates& pos);

	// Add an NPC to the world
	template <class NPC_Type>
		static void AddNPC(const Coordinates& _pos);

	// A trust-based function that hard-codes the tiles around a position to create a vertical doorway.
	static inline void TrustDoorway(const Coordinates& pos);

	// Erase a column, and add a doorway there
	static inline void ColumnToDoor(const Coordinates& pos) {  
		EraseColumn(pos);
		BuildDoorColumn(pos);
	}

	// Erase a column, and add a doorway column above it
	static inline void ColumnToDoorway(const Coordinates& pos) {  
		EraseColumn(pos);
		BuildDoorway(pos);
	}
};