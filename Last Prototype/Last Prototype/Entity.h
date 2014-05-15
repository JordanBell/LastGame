#ifndef Entity_h
#define Entity_h

#include "SDL.h"
#include "toolkit.h"
#include "Tools.h"

class EntityContainer;

class Entity
{
public:
<<<<<<< HEAD
	XY pos;			// The x and y coordinates, relative to the parent's position. If the parent is NULL, then these coordinates are direct.
	
	Entity(float x, float y) : pos( XY(x,y) ), 
							   isInSight(true),
							   parent(NULL),
							   sprite_sheet(NULL) {}
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
	XY getBlittingPos(void) const;

	// Return whether or not a visible part of this object is on the screen. 
	virtual bool IsOnScreen(void) const;

	// Return whether or not this entity's image should be rendered
	bool ShouldRenderImage(void) const;



protected:
	EntityContainer* parent;	// The parent of this Entity
	bool isInSight;				// Whether or not this object is "within sight" of the player
	SDL_Rect skin;				// Section of the sprite_sheet to blit
	SDL_Surface* sprite_sheet;	// The image (from file) which this entity displays



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
=======
	float x, y; // The x and y coordinates, relative to the parent's position. If the parent is NULL, then these coordinates are direct.

	//Constructors
	Entity(float x, float y) : x(x), y(y), skin(NULL), parent(NULL), sprite_sheet(NULL), isInSight(true) {}
	~Entity(void) { SDL_FreeSurface(sprite_sheet); }
	
	void setParent(EntityContainer* parent) {this->parent = parent;}
	void move(int x, int y);
	float getBlittingX(void);
	float getBlittingY(void);
	virtual void update(int delta) {}
	virtual void render(void);

protected:
	bool isInSight;
	EntityContainer* parent;
	SDL_Rect* skin;				// Section of the sprite_sheet to blit
	SDL_Surface* sprite_sheet;	// The image file which this entity is displayed as.

	void blit() { apply_surface(getBlittingX(), getBlittingY(), sprite_sheet, screen, skin); }
	XY* GetGridPosition();
	bool IsOnScreen() { return ((getBlittingX() <= screen->w) && (getBlittingY() <= screen->h)); };
	static XY* GetGridPosition(float _x, float _y);
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
};

#endif