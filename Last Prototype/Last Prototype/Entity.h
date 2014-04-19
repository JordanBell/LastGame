#pragma once
#ifndef Entity_h
#define Entity_h

#include "SDL.h"
#include "toolkit.h"
#include "Tools.h"

class EntityContainer;

class Entity
{
public:
	float x, y; // The x and y coordinates, relative to the parent's position. If the parent is NULL, then these coordinates are direct.

	//Constructors
	Entity(float x, float y) : x(x), y(y), skin(NULL), parent(NULL), sprite_sheet(NULL) {}
	~Entity(void) { SDL_FreeSurface(sprite_sheet); }
	
	void setParent(EntityContainer* parent) {this->parent = parent;}
	float getBlittingX(void);
	float getBlittingY(void);
	virtual void update(int delta) {}
	virtual void render(void) { if (IsOnScreen()) apply_surface(getBlittingX(), getBlittingY(), sprite_sheet, screen, skin); }

protected:
	EntityContainer* parent;
	SDL_Rect* skin;				// Section of the sprite_sheet to blit
	SDL_Surface* sprite_sheet;	// The image file which this entity is displayed as.

	XY* GetGridPosition();
	bool IsOnScreen() { return ((getBlittingX() <= screen->w) && (getBlittingY() <= screen->h)); };
	static XY* GetGridPosition(float _x, float _y);
};

#endif