#include "Resources.h"
#include "toolkit.h"
#include "Player.h"
#include "Environment.h"

#include <stdexcept>
std::string playerSheetFile	  = "playerSheet.png";
std::string environmentSheetFile = "environment.png";

SDL_Surface Resources::GetPlayerSheet()
{
	try { return GetSheet(playerSheet); }
	catch (std::runtime_error e) 
	{
		throw std::runtime_error("The player sheet file failed to load.");
	}
}

SDL_Surface Resources::GetEnvironmentImage()
{
	try { return GetSheet(environmentSheet); }
	catch (std::runtime_error e) 
	{
		throw std::runtime_error("The environment file failed to load.");
	}
}

SDL_Surface Resources::GetSheet(SDL_Surface* sheet)
{
	if (sheet == NULL)
	{
			 if (sheet == playerSheet)		sheet = load_image(playerSheetFile);
		else if (sheet == environmentSheet) sheet = load_image(environmentSheetFile);

		// Check for failures.
		if (sheet == NULL) throw std::runtime_error("The environment file failed to load.");
	}
	else return *sheet;
}
