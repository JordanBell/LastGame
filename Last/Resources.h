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
	// Refer to the player sprite sheet texture
	static SDL_Texture* const GetPlayerImage();
	
	// Refer to the environment sprite sheet texture
	static SDL_Texture* const GetEnvironmentImage();
	
	// Refer to the door sprite sheet texture
	static SDL_Texture* const GetDoorImage();
	
	// Refer to the status sprite sheet texture
	static SDL_Texture* const GetStatusImage();

private:
	Resources(void);
	~Resources(void);

	static const string playerSheetFile;		// The filepath to the player's sprite sheet
	static const string environmentSheetFile;	// The filepath to the environment's sprite sheet
	static const string doorSheetFile;			// The filepath to the door's sprite sheet
	static const string statusSheetFile;			// The filepath to the statuses sprite sheet

	static SDL_Texture* playerSheet;		// The player sprite sheet 
	static SDL_Texture* environmentSheet;	// The environment sprite sheet
	static SDL_Texture* doorSheet;			// The door sprite sheet
	static SDL_Texture* statusSheet;		// The status sprite sheet

	// Getting and loading an image into its texture pointer based on a file name
	static SDL_Texture* const GetImage(const string *filename);
};