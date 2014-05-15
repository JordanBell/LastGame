#pragma once
#include "SDL.h"
#include "SDL_ttf.h"

class Resources
{
<<<<<<< HEAD
public:
	// Refer to the player sprite sheet surface
	static SDL_Surface* const GetPlayerSheet();
	
	// Refer to the environment sprite sheet surface
	static SDL_Surface* const GetEnvironmentImage();
	
	// Refer to the environment sprite sheet surface
	static SDL_Surface* const GetDoorImage();

=======
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
private:
	SDL_Surface* m_PlayerSheet, *m_EnvironmentImage;

public:
	Resources(void);
	~Resources(void);

<<<<<<< HEAD
	static const std::string playerSheetFile; // The filepath to the player's sprite sheet
	static const std::string environmentSheetFile; // The filepath to the environment's sprite sheet
	static const std::string doorSheetFile; // The filepath to the door's sprite sheet

	static SDL_Surface* playerSheet; // The player sprite sheet 
	static SDL_Surface* environmentSheet; // The environment sprite sheet
	static SDL_Surface* doorSheet; // The door sprite sheet
=======
	SDL_Surface* GetPlayerSheet() { return m_PlayerSheet; }
	SDL_Surface* GetEnvironmentImage() { return m_EnvironmentImage; }
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
};

extern Resources* g_resources;

