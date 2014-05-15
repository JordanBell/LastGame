#pragma once
#include "Tools.h"
#include <iostream>

namespace ShapeBuilder
{	
	// WARNING: Does not add option for adding to the top
	// Apply a given Build function in a rectangular pattern
	void BuildRectangle(XY pos, XY dimensions, void (*drawFunction)(XY), bool filled = true);

	//void WorldBuilder::BuildLine(XY start, XY end, bool top, void (*drawFunction)(XY pos) = WorldBuilder::AddTileTo<T>)
	void BuildLine(XY start, XY end, void (*drawFunction)(XY));


	// Straight-up Tile Shapes
	template <class T_Fill, class T_Border>
	void BuildBorderedRectangle(XY pos, XY dimensions, bool top = false)
	{
		// Draw the border
		BuildTileRectangle<T_Border>(pos, dimensions, false, top);
		// Draw the fill
		BuildTileRectangle<T_Fill>(pos+1, dimensions-2, true, top);
	}

	template <class T>
	void BuildTileRectangle(XY pos, XY dimensions, bool filled = true, bool top = false)
	{
		// Call BuildRectangle, with the tile adding function of type T
		if (top)	BuildRectangle(pos, dimensions, WorldBuilder::AddTileToTop<T>, filled);
		else		BuildRectangle(pos, dimensions, WorldBuilder::AddTileToBottom<T>, filled);
	}
}