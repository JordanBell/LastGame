#pragma once
#include "SDL.h"
#include <list>
#include "Entity.h"

class TextureContainer
{
public:
	TextureContainer(const XY& pos) : m_pos(pos) {}
	~TextureContainer(void);

	void AddChild(Entity);

private:
	XY m_pos;
	SDL_Texture* m_container;
	std::list<Entity*> children;
	Entity* parent;
};

