#include "Resources.h"
#include "ToolKit.h"

#include <stdexcept>

// Player sheet consts
const std::string Resources::playerSheetFile = "playerSheet.png";
SDL_Texture* Resources::playerSheet = nullptr;

// Environment sheet consts
const std::string Resources::environmentSheetFile = "environment.png";
SDL_Texture* Resources::environmentSheet = nullptr;

// Door sheet consts
const std::string Resources::doorSheetFile = "doorSheet.png";
SDL_Texture* Resources::doorSheet = nullptr;

// Status sheet consts
const std::string Resources::statusSheetFile = "statusSheet.png";
SDL_Texture* Resources::statusSheet = nullptr;

SDL_Texture* const Resources::GetPlayerImage(void)
{
	try { 
		return GetImage(&playerSheetFile);
	}
	catch (std::runtime_error e)
	{
		printf("Failed to load the player image.");
	}
}

SDL_Texture* const Resources::GetEnvironmentImage(void)
{
	try { 
		return GetImage(&environmentSheetFile);
	}
	catch (std::runtime_error e)
	{
		printf("Failed to load the environment image.");
	}
}

SDL_Texture* const Resources::GetDoorImage(void)
{
	try { 
		return GetImage(&doorSheetFile);
	}
	catch (std::runtime_error e)
	{
		printf("Failed to load the door image.");
	}
}

SDL_Texture* const Resources::GetStatusImage(void)
{
	try { 
		return GetImage(&statusSheetFile);
	}
	catch (std::runtime_error e)
	{
		printf("Failed to load the status image.");
	}
}

SDL_Texture* const Resources::GetImage(const std::string* filename)
{
	// Pointer to the texture pointer
	SDL_Texture** targetPtr = nullptr;
	
		 if (filename == &playerSheetFile)		targetPtr = &playerSheet;
	else if (filename == &environmentSheetFile) targetPtr = &environmentSheet;
	else if (filename == &doorSheetFile)		targetPtr = &doorSheet;
	else if (filename == &statusSheetFile)		targetPtr = &statusSheet;
	else										targetPtr = nullptr;

	// If filename recognised
	if (targetPtr)
	{
		// Load, if not already
		if (*targetPtr == nullptr)
		{
			*targetPtr = LoadImageTexture(*filename);
			SDL_SetTextureBlendMode(*targetPtr, SDL_BLENDMODE_BLEND);

			// Check for failures
			if (!*targetPtr) throw std::runtime_error("Failed to get an image from Resources.");
		}

		return *targetPtr;
	}
	else
	{
		throw std::runtime_error("Failed to recognise the filename in GetImage.");
	}
}