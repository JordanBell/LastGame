//#pragma once
//#include "Tools.h"
//#include "WorldBuilder.h"
//
//#include <iostream>
//
//namespace ShapeBuilder
//{
//	// WARNING: Does not add option for adding to the top
//	/*void jkdhjhdfa(XY pos, XY dimensions, bool filled = true)
//	{
//		
//	}*/
//	
//	//// WARNING: Does not add option for adding to the top
//	//void BuildRect(XY pos, XY dimensions, void (*drawFunction)(XY), bool filled = true)
//	//{
//	//	for (float i = pos.x; i < pos.x + dimensions.x; i++)
//	//	{
//	//		for (float j = pos.y; j < pos.y + dimensions.y; j++)
//	//		{
//	//			if (filled) *drawFunction(XY(i, j));
//	//			else
//	//			{
//	//				XY upperBounds = pos + dimensions - 1;
//	//				const bool xEdge = ((i == pos.x) || (i == upperBounds.x));
//	//				const bool yEdge = ((j == pos.y) || (j == upperBounds.y));
//
//	//				if (xEdge || yEdge) *drawFunction(XY(i, j));
//	//			}
//	//		}
//	//	}
//	//}
//
//	template <class T_Fill, class T_Border>
//	void BuildBorderedRectangle(XY pos, XY dimensions, bool top = false)
//	{
//		// Draw the border
//		BuildTileRectangle<T_Border>(pos, dimensions, false, top);
//		// Draw the fill
//		BuildTileRectangle<T_Fill>(pos+1, dimensions-2, true, top);
//	}
//	
//	//template <class T>
//	void heyAlt() 
//	{ 
//		printf("Hey"); 
//	}
//
//	template <class T>
//	void hey(T thing)
//	{
//		printf("%d", thing);
//	}
//
//	void hey()
//	{
//		printf("Hey");
//	}
//
//	template <class T>
//	void BuildTileRectangle(XY pos, XY dimensions, bool filled = true, bool top = false)
//	{
//		for (float i = pos.x; i < pos.x + dimensions.x; i++)
//		{
//			for (float j = pos.y; j < pos.y + dimensions.y; j++)
//			{
//				if (filled) WorldBuilder::AddTileTo<T>(XY(i, j), top);
//				else
//				{
//					XY upperBounds = pos + dimensions - 1;
//					const bool xEdge = ((i == pos.x) || (i == upperBounds.x));
//					const bool yEdge = ((j == pos.y) || (j == upperBounds.y));
//
//					if (xEdge || yEdge) WorldBuilder::AddTileTo<T>(XY(i, j), top);
//				}
//			}
//		}
//	}
//
//	template <class T>
//	//void WorldBuilder::BuildLine(XY start, XY end, bool top, void (*drawFunction)(XY pos) = WorldBuilder::AddTileTo<T>)
//	void BuildLine(XY start, XY end, bool top = false)
//	{
//		bool xEqual = (start.x == end.x);
//		bool yEqual = (start.y == end.y);
//
//		// Point to the differing coordinates
//		float* differingStart;
//		float* differingEnd;
//
//		// Point to the coordinates that differ
//		if (xEqual)
//		{
//			differingStart = &start.y;
//			differingEnd = &end.y;
//		}
//		else if (yEqual)
//		{
//			differingStart = &start.x;
//			differingEnd = &end.x;
//		}
//		else throw new std::runtime_error("Cannot draw diagonal lines.");
//
//		int directionPolarity = (*differingStart < *differingEnd) ? 1 : -1; // Negative or positive, based on the direction of the line
//
//		XY tileCoords = start; // The coordinates for each tile drawn
//		for (int i = *differingStart; i != *differingEnd + directionPolarity /*Inclusive*/; i += directionPolarity) // i loops through the positions between the two points, in the direction of their differing coordinates
//		{
//			if (xEqual) tileCoords.y = i; // Alter Y
//			if (yEqual) tileCoords.x = i; // Alter X
//		
//			// Add a tile to that position
//			WorldBuilder::AddTileTo<T>(tileCoords, top);
//		}
//	}
//}

//#pragma once
//#include "Tools.h"
//#include "WorldBuilder.h"
//
//#include <iostream>
//
//namespace TestNamespace
//{
//	template <class T>
//	void hey(T thing)
//	{
//		printf("%d", thing);
//	}
//
//	void hey()
//	{
//		printf("Hey");
//	}
//
//	template <class T_Fill, class T_Border>
//	void BuildBorderedRectangle(XY pos, XY dimensions, bool top = false)
//	{
//		// Draw the border
//		BuildTileRectangle<T_Border>(pos, dimensions, false, top);
//		// Draw the fill
//		BuildTileRectangle<T_Fill>(pos+1, dimensions-2, true, top);
//	}
//	
//	template <class T>
//	void heyAlt() { printf("Hey"); }
//
//	template <class T>
//	void BuildTileRectangle(XY pos, XY dimensions, bool filled = true, bool top = false)
//	{
//		for (float i = pos.x; i < pos.x + dimensions.x; i++)
//		{
//			for (float j = pos.y; j < pos.y + dimensions.y; j++)
//			{
//				if (filled) WorldBuilder::AddTileTo<T>(XY(i, j), top);
//				else
//				{
//					XY upperBounds = pos + dimensions - 1;
//					const bool xEdge = ((i == pos.x) || (i == upperBounds.x));
//					const bool yEdge = ((j == pos.y) || (j == upperBounds.y));
//
//					if (xEdge || yEdge) WorldBuilder::AddTileTo<T>(XY(i, j), top);
//				}
//			}
//		}
//	}
//
//	template <class T>
//	//void WorldBuilder::BuildLine(XY start, XY end, bool top, void (*drawFunction)(XY pos) = WorldBuilder::AddTileTo<T>)
//	void BuildLine(XY start, XY end, bool top = false)
//	{
//		bool xEqual = (start.x == end.x);
//		bool yEqual = (start.y == end.y);
//
//		// Point to the differing coordinates
//		float* differingStart;
//		float* differingEnd;
//
//		// Point to the coordinates that differ
//		if (xEqual)
//		{
//			differingStart = &start.y;
//			differingEnd = &end.y;
//		}
//		else if (yEqual)
//		{
//			differingStart = &start.x;
//			differingEnd = &end.x;
//		}
//		else throw new std::runtime_error("Cannot draw diagonal lines.");
//
//		int directionPolarity = (*differingStart < *differingEnd) ? 1 : -1; // Negative or positive, based on the direction of the line
//
//		XY tileCoords = start; // The coordinates for each tile drawn
//		for (int i = *differingStart; i != *differingEnd + directionPolarity /*Inclusive*/; i += directionPolarity) // i loops through the positions between the two points, in the direction of their differing coordinates
//		{
//			if (xEqual) tileCoords.y = i; // Alter Y
//			if (yEqual) tileCoords.x = i; // Alter X
//		
//			// Add a tile to that position
//			WorldBuilder::AddTileTo<T>(tileCoords, top);
//		}
//	}
//}

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