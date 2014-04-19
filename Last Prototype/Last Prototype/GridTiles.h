#pragma once

#include "Entity.h"
#include "Resources.h"
#include "Config.h"



/*------------============ SUPER CLASSES ============------------*/

class GridTile : public Entity {
public:
	bool canMoveThrough;

protected:
	GridTile(float x, float y) : Entity(x*TILE_SIZE, y*TILE_SIZE), canMoveThrough(true) { sprite_sheet = g_resources->GetEnvironmentImage(); }
	~GridTile(void) {}

	void SetTileClip(int index1, int index2)
	{
		SDL_Rect* clip = new SDL_Rect();
		clip->x = index1 * TILE_SIZE;
		clip->y = index2 * TILE_SIZE;
		clip->w = clip->h = TILE_SIZE;

		skin = clip;
	}

	void render(void) {
		Entity::render();
	}
};

/************* SOLID TILE *************/

class GridTileSolid : public GridTile {
protected:
	GridTileSolid(float x, float y) : GridTile(x, y) { canMoveThrough = false; }
};



/*------------============ CHILD TILES ============------------*/

class GrassTile : public GridTile {
public:
	GrassTile(float x, float y) : GridTile(x, y) { SetTileClip(0, 0); }
};

class WoodFloorTile : public GridTile {
public:
	WoodFloorTile(float x, float y) : GridTile(x, y) { SetTileClip(1, 1); }
};

class StoneFloorTile : public GridTile {
public:
	StoneFloorTile(float x, float y) : GridTile(x, y) { SetTileClip(7, 1); }
};

class StoneWallTile : public GridTileSolid {
public:
	StoneWallTile(float x, float y) : GridTileSolid(x, y) { SetTileClip(6, 0); }
};

class ShinyBlockTile : public GridTileSolid {
public:
	ShinyBlockTile(float x, float y) : GridTileSolid(x, y) { SetTileClip(2, 4); }
};

class InvisibleWallTile : public GridTileSolid {
public:
	InvisibleWallTile(float x, float y) : GridTileSolid(x, y) { SetTileClip(3, 4); }
};