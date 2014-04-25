#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

class Resources
{
private:
	SDL_Surface* m_PlayerSheet, *m_EnvironmentImage;

public:
	Resources(void);
	~Resources(void);

	SDL_Surface* GetPlayerSheet() { return m_PlayerSheet; }
	SDL_Surface* GetEnvironmentImage() { return m_EnvironmentImage; }
};

extern Resources* g_resources;

