#pragma once

#include "Entity.h"
#include "Resources.h"
#include "Config.h"



/*------------============ SUPER CLASSES ============------------*/

class GridTile : public Entity {
public:
	bool canMoveThrough; // Whether or not the player can pass over this object

protected:
	GridTile(int x, int y) : Entity(x*TILE_SIZE, y*TILE_SIZE), canMoveThrough(true) { sprite_sheet = Resources::GetEnvironmentImage(); }

	// Set the clip of this tile, based on its index in the Environment sprite sheet
	void SetTileClip(int index1, int index2)
	{
		SDL_Rect clip = SDL_Rect();
		clip.x = index1 * TILE_SIZE;
		clip.y = index2 * TILE_SIZE;
		clip.w = clip.h = TILE_SIZE;

		skin = clip;
	}
};

/************* SOLID TILE *************/

class GridTileSolid : public GridTile {
protected:
	GridTileSolid(int x, int y) : GridTile(x, y) { canMoveThrough = false; }
};



/*------------============ CHILD TILES ============------------*/

class GrassTile : public GridTile {
public:
	GrassTile(int x, int y) : GridTile(x, y) { SetTileClip(0, 0); }
};

class WoodWallTile : public GridTileSolid {
public:
	WoodWallTile(int x, int y) : GridTileSolid(x, y) { SetTileClip(1, 1); }
};

class StoneFloorTile : public GridTile {
public:
	StoneFloorTile(int x, int y) : GridTile(x, y) { SetTileClip(7, 1); }
};

class StoneFloorTile_LightBrown : public GridTile {
public:
	StoneFloorTile_LightBrown(int x, int y) : GridTile(x, y) { SetTileClip(6, 1); }
};

class StoneWallTile : public GridTileSolid {
public:
	StoneWallTile(int x, int y) : GridTileSolid(x, y) { SetTileClip(6, 0); }
};

class ShinyBlockTile : public GridTileSolid {
public:
	ShinyBlockTile(int x, int y) : GridTileSolid(x, y) { SetTileClip(2, 4); }
};

class InvisibleWallTile : public GridTileSolid {
public:
	InvisibleWallTile(int x, int y) : GridTileSolid(x, y) { SetTileClip(3, 4); }
};