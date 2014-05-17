/*Some of this source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

#include "toolkit.h"
#include "Resources.h"
#include <string>

const char* WINDOW_TITLE("Last");
SDL_Window* g_window;
SDL_Surface* g_windowSurface;
SDL_Event event;
bool inFullScreen;

void toggleScreenFormat()
{
	// Change the screen width and height variables to the nearest TILE_SIZE multiple of the native res
	//SCREEN_WIDTH = info->current_w;
	//SCREEN_HEIGHT = info->current_h;
	
	g_window = inFullScreen ? 
		SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
						 WINDOWED_SCREEN_RES.x, 
						 WINDOWED_SCREEN_RES.y,
						 SDL_WINDOW_SHOWN) :
		SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
						 1680, 
						 1050,
						 SDL_WINDOW_FULLSCREEN);

	// Toggle
	inFullScreen = !inFullScreen;
}

inline void exitFullScreen() { if (inFullScreen) toggleScreenFormat(); }

bool SDL_init()
{
	//Init Subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;
    
	//Init Screen
	inFullScreen = !FULL_SCREEN_INITIAL;

	// Initialise the screen
	toggleScreenFormat();

	// Get the window's surface, if its initialisation was successful
	if (g_window == NULL) return false;
	else g_windowSurface = SDL_GetWindowSurface(g_window);
    
	return true;
}

void SDL_deinit()
{
	//Quit all of that
	SDL_Quit();
}

SDL_Surface* load_image(std::string filename)
{
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());
	if (loadedImage != NULL)
	{
		optimizedImage = SDL_ConvertSurface( loadedImage, g_windowSurface->format, NULL);
		SDL_FreeSurface(loadedImage);

		if (optimizedImage != NULL)
		{
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF);
			SDL_SetColorKey(optimizedImage, SDL_TRUE, colorkey);
		}
	}

	return optimizedImage;
}

void apply_surface(const XY& pos, SDL_Surface* source, SDL_Rect* clip)
{
	if (source != NULL)
	{
		SDL_Rect offset;

		offset.x = pos.x;
		offset.y = pos.y;
		SDL_BlitSurface(source, clip, g_windowSurface, &offset);
	}
}