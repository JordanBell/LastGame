#pragma once
#ifndef Entity_h
#define Entity_h

#include "SDL.h"
#include "toolkit.h"

class Entity
{
public:
	float x, y;

	//Constructors
	Entity(int x, int y) : x(x), y(y), skin(NULL) {}
	~Entity(void) { SDL_FreeSurface(sprite_sheet); }
	
	//void setParent(EntityContainer* parent) {this->parent = parent;}
	virtual void update(int delta) {}
	virtual void render(void) { apply_surface(x, y, sprite_sheet, screen, skin); }

protected:
	//EntityContainer* parent;
	SDL_Rect* skin;				// Section of the sprite_sheet to blit
	SDL_Surface* sprite_sheet;	// The image file which this entity is displayed as
};

#endif