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
	screen = inFullScreen ? 
			 SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE) :
			 SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_FULLSCREEN);
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
	inFullScreen = true;
	toggleScreenFormat();
	SDL_WM_SetCaption("Sustainable Economy", NULL);
	if (screen == NULL) return false;
    
	//Init SDL_ttf
	if (TTF_Init() == -1) return false;
    
	return load_files();
}

void SDL_deinit()
{
	//Free all of this
	delete g_resources;

	//Quit all of that
	TTF_Quit();
	SDL_Quit();
}

bool load_files() //Load files, and check for the success of each one
{
	try {
		g_resources = new Resources();
	}
	catch (std::exception &e) {
		printf(e.what());
		return false;
	}

	return true;
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

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
	if (source != NULL)
	{
			SDL_Rect offset;

		offset.x = x;
		offset.y = y;

		SDL_BlitSurface(source, clip, destination, &offset);
	}
}