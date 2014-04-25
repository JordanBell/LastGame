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
	// Return the player sprite sheet surface
	static SDL_Surface GetPlayerSheet();
	
	// Return the environment sprite sheet surface
	static SDL_Surface GetEnvironmentImage();

private:
	Resources(void);
	~Resources(void);

	static const std::string playerSheetFile; // The filepath to the player's sprite sheet
	static const std::string environmentSheetFile; // The filepath to the environment's sprite sheet

	static SDL_Surface* playerSheet; // The player sprite sheet 
	static SDL_Surface* environmentSheet; // The environment sprite sheet

	// Returns a sprite sheet based on the SDL_Surface identifier passed as argument
	static SDL_Surface GetSheet(SDL_Surface* sheet);
};

extern Resources* g_resources;

