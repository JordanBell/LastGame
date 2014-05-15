#pragma once

#include "Entity.h"
#include "Resources.h"
#include "Config.h"
#include "Sprite.h"


/*------------============ SUPER CLASSES ============------------*/

class GridTile : public Sprite {
public:
	bool canMoveThrough; // Whether or not the player can pass over this object

	// Override this function to give the tile a function when being interacted with. If not overriden, nothing will happen.
	virtual void onInteract() {};

protected:
	GridTile(const int x, const int y) : Sprite(x*TILE_SIZE, y*TILE_SIZE), canMoveThrough(true) {}
};

// A GridTile that player's can't move through
class GridTileSolid : public virtual GridTile {
protected:
	GridTileSolid() : GridTile(0, 0) { canMoveThrough = false; }
};

class WorldTile : public virtual GridTile {
protected:
	WorldTile() : GridTile(0, 0) { sprite_sheet = Resources::GetEnvironmentImage(); }

	// Set the clip of this tile, based on its index in the Environment sprite sheet
	void SetTileClip(const int index1, const int index2)
	{
		SDL_Rect clip = SDL_Rect();
		clip.x = index1 * TILE_SIZE;
		clip.y = index2 * TILE_SIZE;
		clip.w = clip.h = TILE_SIZE;

		skin = clip;
	}
};



/*------------============ CHILD TILES ============------------*/

// A door which opens and closes on interact
class Door : public GridTile {
public:
	Door(const int x, const int y) : GridTile(x, y), open(false), inAnimation(false)
	{ 
		max_cycles = numClips*framesPerClip;
		canMoveThrough = open; 
		sprite_sheet = Resources::GetDoorImage();

		// Initialise the clips
		for (int i = 0; i < numClips; i++)
		{
			SDL_Rect clip;
			clip.x = i*TILE_SIZE;
			clip.y = 0;
			clip.w = TILE_SIZE;
			clip.h = TILE_SIZE*1.5;

			clips[i] = clip;
		}
	}

protected:
	static const int framesPerClip = 2;
	static const int numClips = 5;
	SDL_Rect clips[numClips];

	bool open; // Whether or not this door is currently open
	bool inAnimation; // If the door is animating closed or open

	inline void setMoveThrough() { canMoveThrough = open; }

	virtual void render()
	{
		EntityContainer::render();
	}

	// On interaction, open this door.
	void onInteract()
	{
		if (!inAnimation)
		{
			open = !open; // Toggle
			if (!open) setMoveThrough(); // If closing, set the door as closed immediately.
			inAnimation = true; // Start the animation
		}
	}

	void set_skin() { skin = clips[cycle/framesPerClip]; }

	void update(const int delta)
	{
		if (inAnimation)
		{
			if (open) IncCycle(); // Increment if opening
			else	  DecCycle(); // Decrement if closing

			// If at the end of an animation
			if ((cycle == 0) || (cycle == max_cycles-1))
			{
				inAnimation = false;
				setMoveThrough();
			}
		}
	}
};

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

// Blacks
class Tile_Black : public WorldTile {
public:
	Tile_Black(int x, int y) : WorldTile(), GridTile(x, y) { SetTileClip(3, 0); }
};

// Environment Walls
class StoneWallTile : public WorldTile, public GridTileSolid {
public:
	StoneWallTile(int x, int y) : WorldTile(), GridTileSolid(), GridTile(x, y) { SetTileClip(6, 0); }
};
class ShinyBlockTile : public WorldTile, public GridTileSolid {
public:
	ShinyBlockTile(int x, int y) : WorldTile(), GridTileSolid(), GridTile(x, y)  { SetTileClip(2, 4); }
};
class WoodWallTile : public WorldTile, public GridTileSolid {
public:
	WoodWallTile(int x, int y) : WorldTile(), GridTileSolid(), GridTile(x, y)  { SetTileClip(1, 1); }
};
class WoodWallTile_Bottom : public WorldTile {
public:
	WoodWallTile_Bottom(int x, int y) : WorldTile(), GridTile(x, y)  { SetTileClip(4, 0); }
};
class InvisibleWallTile : public WorldTile, public GridTileSolid {
public:
	InvisibleWallTile(int x, int y) : WorldTile(), GridTileSolid(), GridTile(x, y) { SetTileClip(3, 4); }
};