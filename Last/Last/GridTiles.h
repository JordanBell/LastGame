#pragma once

#include "Entity.h"
#include "Resources.h"
#include "Config.h"
#include "Sprite.h"


/*------------============ SUPER CLASSES ============------------*/

class Tile {
	void validateTemplate(Entity e) {};

public:
	bool canMoveThrough; // Whether or not the player can pass over this object

	// Override this function to give the tile a function when being interacted with. If not overriden, nothing will happen.
	virtual void onInteract() {};

protected:
	Tile() : canMoveThrough(true) {}
};


// A Tile and Entity
class TileEntity : public Tile, public Entity 
{
public:
	TileEntity(const int x, const int y) : Entity(x*TILE_SIZE, y*TILE_SIZE) {}
	TileEntity() : Entity(0, 0) {}
};
// A Tile and Animation (Technically not a sprite, as it is not an EntityContainer)
class TileSprite : public TileEntity, public AnimatedObject
{
public:
	TileSprite(const int x, const int y) : TileEntity(x, y) { }
};



class EnvironmentTile : public TileEntity {
protected:
	EnvironmentTile(const int x, const int y) : TileEntity(x, y) { m_spriteSheet = Resources::GetEnvironmentImage();}

	// Set the clip of this tile, based on its index in the Environment sprite sheet
	void SetTileClip(const int index1, const int index2);
};



// A GridTile that player's can't move through
class EnvironmentTileSolid : public EnvironmentTile {
protected:
	EnvironmentTileSolid(const int x, const int y) : EnvironmentTile(x, y) { canMoveThrough = false; }
};



/*------------============ CHILD TILES ============------------*/

// A door which opens and closes on interact
class Door : public TileSprite {
public:
	Door(const int x, const int y);

protected:
	static const int framesPerClip = 2;
	static const int numClips = 5;
	SDL_Rect clips[numClips];

	bool open; // Whether or not this door is currently open
	bool inAnimation; // If the door is animating closed or open

	inline void setMoveThrough() { canMoveThrough = open; }

	// On interaction, open this door.
	void onInteract(void);
	void set_skin() { m_skin = clips[cycle/framesPerClip]; }

	void update(const int delta);
	virtual void render(void) { set_skin(); TileSprite::render(); }
};



// Environment Floors
class GrassTile : public EnvironmentTile {
public:
	GrassTile(const int x, const int y) : EnvironmentTile(x, y) { SetTileClip(2, 0); }
};
class StoneFloorTile : public EnvironmentTile {
public:
	StoneFloorTile(const int x, const int y) : EnvironmentTile(x, y) { SetTileClip(7, 1); }
};
class StoneFloorTile_LightBrown : public EnvironmentTile {
public:
	StoneFloorTile_LightBrown(const int x, const int y) : EnvironmentTile(x, y) { SetTileClip(6, 1); }
};



// Blacks
class Tile_Black : public EnvironmentTile {
public:
	Tile_Black(const int x, const int y) : EnvironmentTile(x, y) { SetTileClip(3, 0); }
};



// Environment Walls
class StoneWallTile : public EnvironmentTileSolid {
public:
	StoneWallTile(const int x, const int y) : EnvironmentTileSolid(x, y) { SetTileClip(6, 0); }
};
class ShinyBlockTile : public EnvironmentTileSolid {
public:
	ShinyBlockTile(const int x, const int y) : EnvironmentTileSolid(x, y)  { SetTileClip(2, 4); }
};
class WoodWallTile : public EnvironmentTileSolid {
public:
	WoodWallTile(const int x, const int y) : EnvironmentTileSolid(x, y)  { SetTileClip(1, 1); }
};
class WoodWallTile_Half : public EnvironmentTile {
public:
	WoodWallTile_Half(const int x, const int y) : EnvironmentTile(x, y)  { SetTileClip(4, 0); }
};
class InvisibleWallTile : public EnvironmentTileSolid {
public:
	InvisibleWallTile(const int x, const int y) : EnvironmentTileSolid(x, y) { SetTileClip(3, 4); }
};