#pragma once
#include "Tools.h"

namespace ShapeBuilder
{	
	// Apply a given Build function in a rectangular pattern
	void BuildRectangle(const Coordinates& pos, const Dimensions& dimensions, void (*drawFunction)(const Coordinates&), bool filled = true);
	// Apply a given Build function in a line
	void BuildLine(Coordinates start, Dimensions end, void (*drawFunction)(const Coordinates&));


	// Straight-up Tile Shapes
	template <class T_Fill, class T_Border>
	void BuildBorderedRectangle(const Coordinates& pos, const Dimensions& dimensions, Layer layer = BOTTOM_LAYER)
	{
		// Draw the border
		BuildTileRectangle<T_Border>(pos, dimensions, false, layer);
		// Draw the fill
		BuildTileRectangle<T_Fill>(pos+1, dimensions-2, true, layer);
	}

	template <class T>
	void BuildTileRectangle(const Coordinates& pos, const Dimensions& dimensions, bool filled = true, Layer layer = BOTTOM_LAYER)
	{
		// Call BuildRectangle, with the tile adding function of type T
		switch (layer) {
			case TOP_LAYER:	   BuildRectangle(pos, dimensions, WorldBuilder::AddToTop<T>, filled);
			case MIDDLE_LAYER: BuildRectangle(pos, dimensions, WorldBuilder::AddToMiddle<T>, filled);
			case BOTTOM_LAYER: BuildRectangle(pos, dimensions, WorldBuilder::AddToBottom<T>, filled);
		}
	}
}