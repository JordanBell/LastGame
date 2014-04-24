#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

/*
Loads and holds the sprite sheets and other resources.
*/
class Resources
{
public:
	static SDL_Surface GetPlayerSheet();
	static SDL_Surface GetEnvironmentImage();

private:
	Resources(void);
	~Resources(void);

	static SDL_Surface* playerSheet;
	static SDL_Surface* environmentSheet;

	static const std::string playerSheetFile;
	static const std::string environmentSheetFile;

	static SDL_Surface GetSheet(SDL_Surface* sheet);
};

extern Resources* g_resources;

