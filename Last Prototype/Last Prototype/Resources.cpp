#include "Resources.h"
#include "toolkit.h"
#include "Player.h"
#include "Environment.h"

#include <stdexcept>
Resources* g_resources = NULL;

<<<<<<< HEAD
// Player sheet consts
const std::string Resources::playerSheetFile = (TILE_SIZE==32) ? "playerSheet.png" : "playerSheet16Bit.png";
SDL_Surface* Resources::playerSheet = NULL;

// Environment sheet consts
const std::string Resources::environmentSheetFile = (TILE_SIZE==32) ? "environment.png" : "environment16Bit.png";
SDL_Surface* Resources::environmentSheet = NULL;

// Door sheet consts
const std::string Resources::doorSheetFile = "doorSheet.png";
SDL_Surface* Resources::doorSheet = NULL;

SDL_Surface* const Resources::GetPlayerSheet()
{
	if (playerSheet == NULL)
	{
		playerSheet = load_image(playerSheetFile);

		// Check for failures
		if (!playerSheet) throw std::runtime_error("The player sheet file failed to load.");
	}

	return playerSheet;
}

SDL_Surface* const Resources::GetEnvironmentImage()
{
	if (environmentSheet == NULL)
	{
		environmentSheet = load_image(environmentSheetFile);

		// Check for failures
		if (!environmentSheet) throw std::runtime_error("The environment file failed to load.");
	}

	return environmentSheet;
}

SDL_Surface* const Resources::GetDoorImage()
{
	if (doorSheet == NULL)
	{
		doorSheet = load_image(doorSheetFile);

		// Check for failures
		if (!doorSheet) throw std::runtime_error("The door file failed to load.");
	}

	return doorSheet;
}
=======
Resources::Resources(void)
{
	// Load the resouce files using SDL
	m_PlayerSheet =			load_image("playerSheet.png");
	m_EnvironmentImage =	load_image("environment.png");

	// Check for failures.
	if ((m_PlayerSheet		  == NULL)	||
		(m_EnvironmentImage   == NULL)) 
		{
			throw std::runtime_error("Some of the resources failed to initialise");
		}
}

Resources::~Resources(void)
{
	// Free that shit
	SDL_FreeSurface(m_PlayerSheet);
	SDL_FreeSurface(m_EnvironmentImage);
}
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
