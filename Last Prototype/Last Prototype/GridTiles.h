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



// A Tile contains both the members of the GridTile, and one of the Entity classes
class TileEntity : public Tile, public Entity 
{
public:
	TileEntity(const int x, const int y) : Entity(x*TILE_SIZE, y*TILE_SIZE) {}
	TileEntity() : Entity(0, 0) {}
};

class TileSprite : public TileEntity, public AnimatedObject
{
public:
	TileSprite(const int x, const int y) : TileEntity(x, y) { }
};



class EnvironmentTile : public TileEntity {
protected:
	EnvironmentTile(const int x, const int y) : TileEntity(x, y) { sprite_sheet = Resources::GetEnvironmentImage(); }

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
class EnvironmentTileSolid : public EnvironmentTile {
protected:
	EnvironmentTileSolid(const int x, const int y) : EnvironmentTile(x, y) { canMoveThrough = false; }
};



/*------------============ CHILD TILES ============------------*/

// A door which opens and closes on interact
class Door : public TileSprite {
public:
	Door(const int x, const int y) : TileSprite(x, y), open(false), inAnimation(false)
	{ 
		max_cycles = numClips*framesPerClip;
		canMoveThrough = open; 
		sprite_sheet = Resources::GetDoorImage();
		blitOffset = XY(0, -TILE_SIZE/2);

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