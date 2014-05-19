#pragma once
#include "SDL.h"
#include <string>

/*
Loads and holds the sprite sheets and other resources.
*/
class Resources
{
public:
	// Refer to the player sprite sheet surface
	static SDL_Surface* const GetPlayerImage();
	
	// Refer to the environment sprite sheet surface
	static SDL_Surface* const GetEnvironmentImage();
	
	// Refer to the environment sprite sheet surface
	static SDL_Surface* const GetDoorImage();

private:
	Resources(void);
	~Resources(void);

	static const std::string playerSheetFile;		// The filepath to the player's sprite sheet
	static const std::string environmentSheetFile;	// The filepath to the environment's sprite sheet
	static const std::string doorSheetFile;			// The filepath to the door's sprite sheet

	static SDL_Surface* playerSheet;		// The player sprite sheet 
	static SDL_Surface* environmentSheet;	// The environment sprite sheet
	static SDL_Surface* doorSheet;			// The door sprite sheet

	// Getting and loading an image into its texture pointer based on a file name
	static SDL_Surface* const GetImage(const std::string *filename);
};