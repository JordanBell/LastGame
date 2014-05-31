#pragma once
#include "Tools.h"

namespace ShapeBuilder
{	
	// Apply a given Build function in a rectangular pattern
	void BuildRectangle(const Coordinates& pos, 
						const Dimensions& dimensions, 
						void (*drawFunction)(const Coordinates&), 
						bool filled = true);

	// Apply a given Build function in a line
	void BuildLine(Coordinates start, 
				   Dimensions end, 
				   void (*drawFunction)(const Coordinates&));

	// Straight-up Tile Shapes
	template <class Tile_Fill, class Tile_Border>
	void BuildBorderedRectangle(const Coordinates& pos, 
								const Dimensions& dimensions, 
								Layer layer = BOTTOM_LAYER);

	// Build a simple rectangle with a given tile type.
	template <class TileType>
	void BuildTileRectangle(const Coordinates& pos, 
							const Dimensions& dimensions, 
							bool filled = true, 
							Layer layer = BOTTOM_LAYER)
	{
		// Call BuildRectangle, with the tile adding function of type TileType
		switch (layer) {
			case TOP_LAYER:	   BuildRectangle(pos, dimensions, WorldBuilder::AddToTop<TileType>, filled);
			case MIDDLE_LAYER: BuildRectangle(pos, dimensions, WorldBuilder::AddToMiddle<TileType>, filled);
			case BOTTOM_LAYER: BuildRectangle(pos, dimensions, WorldBuilder::AddToBottom<TileType>, filled);
		}
	}
}