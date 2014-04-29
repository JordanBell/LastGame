//The headers
#include "toolkit.h"
#include "Resources.h"

SDL_Surface* screen;
TTF_Font* font;
SDL_Color textColor = { 0, 0, 0 };
SDL_Event event;
bool inFullScreen;

void toggleScreenFormat()
{
	// Get the native screen resolution
	const SDL_VideoInfo* info = SDL_GetVideoInfo();

	// Change the screen width and height variables to the nearest TILE_SIZE multiple of the native res
	//SCREEN_WIDTH = info->current_w;
	//SCREEN_HEIGHT = info->current_h;
	
	screen = inFullScreen ? 
			 SDL_SetVideoMode(WINDOWED_SCREEN_RES.x, WINDOWED_SCREEN_RES.y, SCREEN_BPP, SDL_SWSURFACE) :
			 SDL_SetVideoMode(info->current_w,		 info->current_h,		SCREEN_BPP, SDL_FULLSCREEN);
	inFullScreen = !inFullScreen;
}

void exitFullScreen()
{
	if (inFullScreen) screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
}

bool SDL_init()
{
	//Init Subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;
    
	//Init Screen
	inFullScreen = !FULL_SCREEN;
	toggleScreenFormat();
	SDL_WM_SetCaption("Sustainable Economy", NULL);
	if (screen == NULL) return false;
    
	//Init SDL_ttf
	if (TTF_Init() == -1) return false;
    
	return true;
}

void SDL_deinit()
{
	//Quit all of that
	TTF_Quit();
	SDL_Quit();
}

SDL_Surface* load_image(std::string filename)
{
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());
	if (loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);

		if (optimizedImage != NULL)
		{
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF);
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
		}
	}

	return optimizedImage;
}

void apply_surface(XY pos, SDL_Surface source, SDL_Surface* destination, SDL_Rect* clip)
{
	if (&source != NULL)
	{
		SDL_Rect offset;

		offset.x = pos.x;
		offset.y = pos.y;

		SDL_BlitSurface(&source, clip, destination, &offset);
	}
}