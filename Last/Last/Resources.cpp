#pragma warning(disable: 4715)
#include "Resources.h"
#include "ToolKit.h"

#include <stdexcept>

// Player sheet consts
const std::string Resources::playerSheetFile = "playerSheet.png";
SDL_Surface* Resources::playerSheet = NULL;

// Environment sheet consts
const std::string Resources::environmentSheetFile = "environment.png";
SDL_Surface* Resources::environmentSheet = NULL;

// Door sheet consts
const std::string Resources::doorSheetFile = "doorSheet.png";
SDL_Surface* Resources::doorSheet = NULL;

SDL_Surface* const Resources::GetPlayerImage()
{
	try { 
		return GetImage(&playerSheetFile);
	}
	catch (std::runtime_error e)
	{
		printf("Failed to load the player image.");
	}

	//// Load if not already
	//if (playerSheet == NULL)
	//{
	//	playerSheet = load_image(environmentSheetFile);

	//	// Check for failures
	//	if (!playerSheet) throw std::runtime_error("The environment file failed to load.");
	//}

	//return playerSheet;
}

SDL_Surface* const Resources::GetEnvironmentImage()
{
	try { 
		return GetImage(&environmentSheetFile);
	}
	catch (std::runtime_error e)
	{
		printf("Failed to load the environment image.");
	}

	//// Load if not already
	//if (environmentSheet == NULL)
	//{
	//	environmentSheet = load_image(environmentSheetFile);

	//	// Check for failures
	//	if (!environmentSheet) throw std::runtime_error("The environment file failed to load.");
	//}

	//return environmentSheet;
}

SDL_Surface* const Resources::GetDoorImage()
{
	try { 
		return GetImage(&doorSheetFile);
	}
	catch (std::runtime_error e)
	{
		printf("Failed to load the door image.");
	}

	//// Load if not already
	//if (doorSheet == NULL)
	//{
	//	doorSheet = load_image(doorSheetFile);

	//	// Check for failures
	//	if (!doorSheet) throw std::runtime_error("The door file failed to load.");
	//}

	//return doorSheet;
}

SDL_Surface* const Resources::GetImage(const std::string* filename)
{
	// Pointer to the texture pointer
	SDL_Surface** targetPtr = NULL;
	
		 if (filename == &playerSheetFile)		targetPtr = &playerSheet;
	else if (filename == &environmentSheetFile) targetPtr = &environmentSheet;
	else if (filename == &doorSheetFile)		targetPtr = &doorSheet;

	// Load if not already
	if (targetPtr)
	{
		if (*targetPtr == NULL)
		{
			*targetPtr = LoadImageSurface(*filename);

			// Check for failures
			if (!*targetPtr) throw std::runtime_error("Failed to get an image from Resources.");
		}

		return *targetPtr;
	}
	else
	{
		printf("Stop trying to be efficient, this doesn't work. filename: %s\n", *filename);
		throw std::runtime_error("Failed to recognise the filename in GetImage.");
	}
}