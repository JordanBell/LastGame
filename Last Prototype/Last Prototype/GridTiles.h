#pragma once

#include "Entity.h"
#include "Resources.h"
#include "Config.h"
#include "Sprite.h"


/*------------============ SUPER CLASSES ============------------*/

class GridTile : public Entity {
public:
	bool canMoveThrough; // Whether or not the player can pass over this object

	// Override this function to give the tile a function when being interacted with. If not overriden, nothing will happen.
	virtual void onInteract() {};

protected:
	GridTile(int x, int y) : Entity(x*TILE_SIZE, y*TILE_SIZE), canMoveThrough(true) {}
};

class WorldTile : public virtual GridTile {
protected:
	WorldTile() : GridTile(0, 0) { sprite_sheet = Resources::GetEnvironmentImage(); }

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

// A GridTile that 
class GridTile_Sprite : public virtual GridTile, public virtual Sprite {
public:
	bool canMoveThrough; // Whether or not the player can pass over this object

	// Override this function to give the tile a function when being interacted with. If not overridden, nothing will happen.
	virtual void onInteract() {};

protected:
	GridTile_Sprite() : Sprite(0, 0), GridTile(0, 0) {}
};

// A GridTile that player's can't move through
class GridTileSolid : public virtual GridTile {
protected:
	GridTileSolid() : GridTile(0, 0) { canMoveThrough = false; }
};

//// A door which opens and closes on interact
//class Door : public GridTile_Sprite {
//protected:
//	const int numClips = 5;
//
//	bool open; // Whether or not this door is currently open
//	bool inAnimation;
//	SDL_Rect clips[3];
//
//	Door(int x, int y) : GridTile_Sprite(x, y), Sprite(x*TILE_SIZE, y*TILE_SIZE), open(false), inAnimation(false) 
//	{ 
//		canMoveThrough = false; 
//
//		// Initialise the clips
//		for (int i = 0; i < numClips; i++)
//		{
//			SDL_Rect clip;
//			clip.x = i;
//			clip.y = 0;
//			clip.w = clip.h = TILE_SIZE;
//		}
//	}
//
//	// On interaction, open this door.
//	void onInteract()
//	{
//		open = !open;
//		//inAnimation = true;
//	}
//
//	void set_skin()
//	{
//
//	}
//
//	void update(int delta)
//	{
//		set_skin();
//
//		/*if (inAnimation)
//		{
//			if (open)
//			IncCycle();
//
//			// If at the end of an animation
//			if ((cycle == 0) || (cycle == max_cycles-1))
//			{
//				inAnimation = false;
//			}
//		}*/
//	}
//};



/*------------============ CHILD TILES ============------------*/

// Environment Floors
class GrassTile : public WorldTile {
public:
	GrassTile(int x, int y) : WorldTile(), GridTile(x, y) { SetTileClip(2, 0); }
};
class StoneFloorTile : public WorldTile {
public:
	StoneFloorTile(int x, int y) : WorldTile(), GridTile(x, y) { SetTileClip(7, 1); }
};
class StoneFloorTile_LightBrown : public WorldTile {
public:
	StoneFloorTile_LightBrown(int x, int y) : WorldTile(), GridTile(x, y) { SetTileClip(6, 1); }
};

// Environment Walls
class StoneWallTile : public WorldTile, public GridTileSolid {
public:
	StoneWallTile(int x, int y) : WorldTile(), GridTileSolid(), GridTile(x, y) { SetTileClip(6, 0); }
};
class WoodWallTile : public WorldTile, public GridTileSolid {
public:
	WoodWallTile(int x, int y) : WorldTile(), GridTileSolid(), GridTile(x, y)  { SetTileClip(1, 1); }
};
class ShinyBlockTile : public WorldTile, public GridTileSolid {
public:
	ShinyBlockTile(int x, int y) : WorldTile(), GridTileSolid(), GridTile(x, y)  { SetTileClip(2, 4); }
};
class InvisibleWallTile : public WorldTile, public GridTileSolid {
public:
	InvisibleWallTile(int x, int y) : WorldTile(), GridTileSolid(), GridTile(x, y)  { SetTileClip(3, 4); }
};