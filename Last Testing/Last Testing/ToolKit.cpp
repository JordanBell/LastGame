#include "ToolKit.h"
#include "Config.h"
#include "Renderer_Wrapper.h"
#include "SDL.h"
#include "SDL_image.h"

Window* g_window = NULL;
Renderer* g_renderer = NULL;
bool inFullScreen;
SDL_Event event;

SDL_Rect RectFromXY(Coordinates pos, Dimensions dims) 
{ 
	SDL_Rect r_rect = 
		{pos.x, pos.y, 
		dims.x, dims.y}; 
	return r_rect; 
}

// Deprecated - use Renderer_Wrapper::LoadImageTexture instead
SDL_Surface* LoadImageSurface(std::string filename)
{
	SDL_Surface* r_surface = NULL;

	r_surface = IMG_Load(filename.c_str());
	if (r_surface == NULL) {
		printf("Unable to load image: %s\n", filename.c_str());
	}

	return r_surface;
}

bool TextureHasAccess(SDL_Texture* texture, Uint32 queriedAccess)
{
	int textureAccess;
	SDL_QueryTexture(texture, NULL, &textureAccess, NULL, NULL);

	return (ContainsBit(textureAccess, queriedAccess));
}

bool ContainsBit(int target, int query)
{
	return ((target & query) != 0);
}
