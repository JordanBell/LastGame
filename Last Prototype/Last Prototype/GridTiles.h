#pragma once

#include "Entity.h"
#include "Resources.h"
#include "Config.h"
#include "Sprite.h"


/*------------============ SUPER CLASSES ============------------*/

template <class E>
class GridTile : public E {
	void validateTemplate(Entity e) {};

public:
	bool canMoveThrough; // Whether or not the player can pass over this object

	// Override this function to give the tile a function when being interacted with. If not overriden, nothing will happen.
	virtual void onInteract() {};

protected:
	GridTile(const int x, const int y) : E(x*TILE_SIZE, y*TILE_SIZE), canMoveThrough(true) 
	{ 
		try { validateTemplate(E(0, 0)); }
		catch (runtime_error e) { 
			printf("GridTiles must implement an Entity class or Entity subclass.");
			throw e;
		}
	}
};



class WorldTile : public GridTile<Entity> {
protected:
	WorldTile(const int x, const int y) : GridTile<Entity>(x, y) { sprite_sheet = Resources::GetEnvironmentImage(); }

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



// A GridTile that player's can't move through
class WorldTileSolid : public WorldTile {
protected:
	WorldTileSolid(const int x, const int y) : WorldTile(x, y) { canMoveThrough = false; }
};



/*------------============ CHILD TILES ============------------*/

// A door which opens and closes on interact
class Door : public GridTile<Sprite> {
public:
	Door(const int x, const int y) : GridTile<Sprite>(x, y), open(false), inAnimation(false)
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
	GrassTile(const int x, const int y) : WorldTile(x, y) { SetTileClip(2, 0); }
};
class StoneFloorTile : public WorldTile {
public:
	StoneFloorTile(const int x, const int y) : WorldTile(x, y) { SetTileClip(7, 1); }
};
class StoneFloorTile_LightBrown : public WorldTile {
public:
	StoneFloorTile_LightBrown(const int x, const int y) : WorldTile(x, y) { SetTileClip(6, 1); }
};



// Blacks
class Tile_Black : public WorldTile {
public:
	Tile_Black(const int x, const int y) : WorldTile(x, y) { SetTileClip(3, 0); }
};



// Environment Walls
class StoneWallTile : public WorldTileSolid {
public:
	StoneWallTile(const int x, const int y) : WorldTileSolid(x, y) { SetTileClip(6, 0); }
};
class ShinyBlockTile : public WorldTileSolid {
public:
	ShinyBlockTile(const int x, const int y) : WorldTileSolid(x, y)  { SetTileClip(2, 4); }
};
class WoodWallTile : public WorldTileSolid {
public:
	WoodWallTile(const int x, const int y) : WorldTileSolid(x, y)  { SetTileClip(1, 1); }
};
class WoodWallTile_Bottom : public WorldTile {
public:
	WoodWallTile_Bottom(const int x, const int y) : WorldTile(x, y)  { SetTileClip(4, 0); }
};
class InvisibleWallTile : public WorldTileSolid {
public:
	InvisibleWallTile(const int x, const int y) : WorldTileSolid(x, y) { SetTileClip(3, 4); }
};