#pragma once
#include "sprite.h"
class GridTile : public Entity
{
public:
	GridTile(SDL_Rect* _skin) : Entity(0, 0) {skin = _skin;}
	~GridTile(void) {}
};

