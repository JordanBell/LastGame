#include "ToolKit.h"
#include "Config.h"
#include "Renderer_Wrapper.h"
#include "SDL.h"
#include "SDL_image.h"

bool inFullScreen;

Window* g_window = new Window();
Renderer* g_renderer = new Renderer(g_window);
SDL_Event event;

SDL_Rect RectFromXY(Coordinates pos, Dimensions dims) 
{ 
	SDL_Rect r_rect = 
		{pos.x, pos.y, 
		dims.x, dims.y}; 
	return r_rect; 
}

SDL_Surface* LoadImageSurface(std::string filename)
{
	SDL_Surface* r_surface = NULL;

	r_surface = IMG_Load(filename.c_str());
	if (r_surface == NULL) {
		printf("Unable to load image: %s\n", filename.c_str());
	}

	return r_surface;
}