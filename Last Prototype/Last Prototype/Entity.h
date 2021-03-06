#ifndef Entity_h
#define Entity_h

#include "SDL.h"
#include "toolkit.h"
#include "Tools.h"

class EntityContainer;

class Entity
{
public:
	XY pos;			// The x and y coordinates, relative to the parent's position. If the parent is NULL, then these coordinates are direct.
	
	Entity(float x, float y) : pos( XY(x,y) ), 
							   isInSight(true),
							   parent(NULL),
							   sprite_sheet(NULL),
							   blitOffset(0, 0) {}
	virtual ~Entity(void) {}
	
	// Move this object's coordinates by a displacement amount
	virtual void move(const XY& displacement) { pos += displacement; }
	
	// Update this object's data, make available a delta value depicting the time since the last update
	virtual void update(const int delta) {}
	
	// Entity rendering, which filters out off-screen objects before calling the virtual render function
	void e_render(void);

	// Set an EntityContainer as this object's parent.
	void setParent(EntityContainer* p) {parent = p;}

	// Get the blitting position of this object
	XY getBlittingPos(void) const { return getAbsolutePos() + blitOffset; }

	// Get the absolute position of this object
	XY getAbsolutePos(void) const;

	// Return whether or not a visible part of this object is on the screen. 
	virtual bool IsOnScreen(void) const;

	// Return whether or not this entity's image should be rendered
	bool ShouldRenderImage(void) const;

	void SetSpriteSheet(SDL_Surface* ss) { sprite_sheet = ss; }

	void SetSkin(SDL_Rect _skin) { skin = _skin; }



protected:
	EntityContainer* parent;	// The parent of this Entity
	bool isInSight;				// Whether or not this object is "within sight" of the player
	SDL_Rect skin;				// Section of the sprite_sheet to blit
	SDL_Surface* sprite_sheet;	// The image (from file) which this entity displays
	XY blitOffset;				// The number of pixels from the origin that this object is blitted



	// Render this object - may be overridden
	virtual void render(void) { blit(); }

	// Apply this object's sprite sheet onto the screen at this object's blitting position
	void blit(void);

	// Return whether or not this object is within viewing range of the player
	bool IsInSight(void) const;

	// Get this object's position on the grid (pos/TILE_SIZE)
	XY GetGridPosition(void) const { return GetGridPosition(pos); }

	// Get a set of coordinates' position on the grid (pos/TILE_SIZE)
	static XY GetGridPosition(const XY& _pos);
};

#endif