#ifndef Entity_h
#define Entity_h

#include "SDL.h"
#include "toolkit.h"
#include "Tools.h"

class EntityContainer;

class Entity
{
public:
	// The x and y coordinates, relative to the parent's position. If the parent is NULL, then these coordinates are direct.
	XY pos;
	// Shortcut pointers to the individual values in the pos struct
	float *x, *y; 

	//Constructors
	Entity(float x, float y) : pos( XY(x,y) ), x(&pos.x), y(&pos.y), skin(NULL), parent(NULL), sprite_sheet(NULL), isInSight(true) {}
	~Entity(void) { SDL_FreeSurface(sprite_sheet); }
	
	// Functions
	void setParent(EntityContainer* parent) {this->parent = parent;}
	void move(XY displacement);
	float getBlittingX(void);
	float getBlittingY(void);
	XY getBlittingPos(void);
	virtual void update(int delta) {}
	virtual void render(void);

protected:
	bool isInSight;
	EntityContainer* parent;
	SDL_Rect* skin;				// Section of the sprite_sheet to blit
	SDL_Surface* sprite_sheet;	// The image file which this entity is displayed as.

	// Functions
	void blit() { apply_surface(getBlittingX(), getBlittingY(), sprite_sheet, screen, skin); }
	bool IsOnScreen() { return ((getBlittingX() <= screen->w) && (getBlittingY() <= screen->h)); };
	XY GetGridPosition();
	static XY GetGridPosition(XY _pos);
};

#endif