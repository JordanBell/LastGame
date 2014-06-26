#pragma once
#include "Entity.h"
#include "ConfigTiles.h"
#include "Config.h"

/*------------============ SUPER CLASSES ============------------*/

class Tile : public Entity 
{
protected:
	Tile(const Coordinates& _pos, const Coordinates& _tileIndex, EntityFormat format = TILE_FLOOR_FRMT) 
		: Entity(_pos,
				 Coordinates(0, 0),
				 SSID_ENVIRONMENT,
				 format,
				 &GetTileClip(_tileIndex),
				 nullptr) {}

private:
	// Get the clip of a tile, based on its tile index in the Environment sprite sheet
	static SDL_Rect GetTileClip(const Coordinates& TileIndex);
};

// Floors
class TileIntangible: public Tile {
protected: 
	TileIntangible(const Coordinates& _pos, const Coordinates& _tileIndex) : Tile(_pos, _tileIndex) {}
};
typedef TileIntangible Floor;

// Walls
class TileTangible: public Tile {
protected: 
	TileTangible(const Coordinates& _pos, const Coordinates& _tileIndex) : Tile(_pos, _tileIndex, TILE_WALL_FRMT) {}
};
typedef TileTangible Wall;


/*------------============ CHILD CLASSES ============------------*/

/*** GRASS ***/
class Grass_Base1_Day : public Floor {
public:
	Grass_Base1_Day(const Coordinates& _pos) : Floor(_pos, TILE_INDEX_GRS_BSE1_DAY) {}
};
class Grass_Base2_Day : public Floor {
public:
	Grass_Base2_Day(const Coordinates& _pos) : Floor(_pos, TILE_INDEX_GRS_BSE2_DAY) {}
};
class Grass_Thin1_Day : public Floor {
public:
	Grass_Thin1_Day(const Coordinates& _pos) : Floor(_pos, TILE_INDEX_GRS_THN1_DAY) {}
};
class Grass_Thin2_Day : public Floor {
public:
	Grass_Thin2_Day(const Coordinates& _pos) : Floor(_pos, TILE_INDEX_GRS_THN2_DAY) {}
};


class Grass_Thick1_Day : public Floor {
public:
	Grass_Thick1_Day(const Coordinates& _pos) : Floor(_pos, TILE_INDEX_GRS_THCK1_DAY) {}
};
class Grass_Thick2_Day : public Floor {
public:
	Grass_Thick2_Day(const Coordinates& _pos) : Floor(_pos, TILE_INDEX_GRS_THCK2_DAY) {}
};
class Grass_Thick3_Day : public Floor {
public:
	Grass_Thick3_Day(const Coordinates& _pos) : Floor(_pos, TILE_INDEX_GRS_THCK3_DAY) {}
};
class Grass_Thick4_Day : public Floor {
public:
	Grass_Thick4_Day(const Coordinates& _pos) : Floor(_pos, TILE_INDEX_GRS_THCK4_DAY) {}
};

/***  FLOORS  ***/
class StoneFloorTile : public Floor {
public:
	StoneFloorTile(const Coordinates& _pos) : Floor(_pos, TILE_INDEX_STNFLR) {}
};
class StoneFloorTile_LightBrown : public Floor {
public:
	StoneFloorTile_LightBrown(const Coordinates& _pos) : Floor(_pos, TILE_INDEX_STNFLRBRN) {}
};


// Intangibles
class TileBlack : public TileIntangible {
public:
	TileBlack(const Coordinates& _pos) : TileIntangible(_pos, TILE_INDEX_BLK) {}
};
class WoodWallTile_Above : public TileIntangible {
public:
	WoodWallTile_Above(const Coordinates& _pos) : TileIntangible(_pos, TILE_INDEX_WDWLLHLF) {}
};


/***  WALLS  ***/
class StoneWallTile : public Wall {
public:
	StoneWallTile(const Coordinates& _pos) : Wall(_pos, TILE_INDEX_STNWLL) {}
};
class WoodWallTile : public Wall {
public:
	WoodWallTile(const Coordinates& _pos) : Wall(_pos, TILE_INDEX_WDWLL) {}
};
class WoodWallTile_Half : public Wall {
public:
	WoodWallTile_Half(const Coordinates& _pos) : Wall(_pos, TILE_INDEX_WDWLLHLF) {}
};
class ShinyBlockTile : public Wall {
public:
	ShinyBlockTile(const Coordinates& _pos) : Wall(_pos, TILE_INDEX_SHNY) {}
};
class InvisibleWallTile : public Wall {
public:
	InvisibleWallTile(const Coordinates& _pos) : Wall(_pos, TILE_INDEX_INVSBL) {}
};