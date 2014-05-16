#pragma once
#include "Tools.h"
#include <iostream>

namespace ShapeBuilder
{	
	// Apply a given Build function in a rectangular pattern
	void BuildRectangle(const XY& pos, const XY& dimensions, void (*drawFunction)(const XY&), bool filled = true);
	// Apply a given Build function in a line
	void BuildLine(XY start, XY end, void (*drawFunction)(const XY&));


	// Straight-up Tile Shapes
	template <class T_Fill, class T_Border>
	void BuildBorderedRectangle(const XY& pos, const XY& dimensions, bool top = false)
	{
		// Draw the border
		BuildTileRectangle<T_Border>(pos, dimensions, false, top);
		// Draw the fill
		BuildTileRectangle<T_Fill>(pos+1, dimensions-2, true, top);
	}

	template <class T>
	void BuildTileRectangle(const XY& pos, const XY& dimensions, bool filled = true, bool top = false)
	{
		// Call BuildRectangle, with the tile adding function of type T
		if (top)	BuildRectangle(pos, dimensions, WorldBuilder::AddTileToTop<T>, filled);
		else		BuildRectangle(pos, dimensions, WorldBuilder::AddTileToBottom<T>, filled);
	}
}