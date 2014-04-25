#pragma warning(disable: 4715)
#include "Resources.h"
#include "toolkit.h"
#include "Player.h"
#include "Environment.h"

#include <stdexcept>

// Player sheet consts
const std::string Resources::playerSheetFile = "playerSheet.png";
SDL_Surface* Resources::playerSheet = NULL;

// Environment sheet consts
const std::string Resources::environmentSheetFile = "environment.png";
SDL_Surface* Resources::environmentSheet = NULL;

SDL_Surface Resources::GetPlayerSheet()
{
	if (playerSheet == NULL)
	{
		playerSheet = load_image(playerSheetFile);

		// Check for failures
		if (!playerSheet) throw std::runtime_error("The player sheet file failed to load.");
	}

	return *playerSheet;
}

SDL_Surface Resources::GetEnvironmentImage()
{
	if (environmentSheet == NULL)
	{
		environmentSheet = load_image(environmentSheetFile);

		// Check for failures
		if (!environmentSheet) throw std::runtime_error("The environment file failed to load.");
	}

	return *environmentSheet;
}

//SDL_Surface Resources::GetPlayerSheet()
//{
//	try { return GetSheet(playerSheet); }
//	catch (std::runtime_error e) 
//	{
//		throw std::runtime_error("The player sheet file failed to load.");
//	}
//}
//
//SDL_Surface Resources::GetEnvironmentImage()
//{
//	try { return GetSheet(environmentSheet); }
//	catch (std::runtime_error e) 
//	{
//		throw std::runtime_error("The environment file failed to load.");
//	}
//}
//
//SDL_Surface Resources::GetSheet(SDL_Surface* sheet)
//{
//	if (sheet == NULL)
//	{
//			 if (sheet == playerSheet)		*sheet = *load_image(playerSheetFile);
//		else if (sheet == environmentSheet) *sheet = *load_image(environmentSheetFile);
//
//		// Check for failures
//		if (!sheet) throw std::runtime_error("The environment file failed to load.");
//	}
//	else return *sheet;
//}