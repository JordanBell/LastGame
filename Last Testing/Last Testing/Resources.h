#pragma once
#include "SDL.h"
#include <string>
using namespace std;

/*
Loads and holds the sprite sheets and other resources.
*/
class Resources
{
public:
	// Refer to the player sprite sheet surface
	static SDL_Texture* const GetPlayerImage();
	
	// Refer to the environment sprite sheet surface
	static SDL_Texture* const GetEnvironmentImage();
	
	// Refer to the environment sprite sheet surface
	static SDL_Texture* const GetDoorImage();

private:
	Resources(void);
	~Resources(void);

	static const string playerSheetFile;		// The filepath to the player's sprite sheet
	static const string environmentSheetFile;	// The filepath to the environment's sprite sheet
	static const string doorSheetFile;			// The filepath to the door's sprite sheet

	static SDL_Texture* playerSheet;		// The player sprite sheet 
	static SDL_Texture* environmentSheet;	// The environment sprite sheet
	static SDL_Texture* doorSheet;			// The door sprite sheet

	// Getting and loading an image into its texture pointer based on a file name
	static SDL_Texture* const GetImage(const string *filename);
};