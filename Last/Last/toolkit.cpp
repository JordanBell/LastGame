#include "ToolKit.h"
#include "Config.h"
#include "Renderer_Wrapper.h"
#include "SDL.h"
#include "SDL_image.h"

Window* g_window = nullptr;
Renderer* g_renderer = nullptr;
bool inFullScreen;
SDL_Event event;

SDL_Rect RectFromXY(Coordinates pos, Dimensions dims) 
{ 
	SDL_Rect r_rect = 
		{pos.x, pos.y, 
		dims.x, dims.y}; 
	return r_rect; 
}

bool TextureHasAccess(SDL_Texture* texture, Uint32 queriedAccess)
{
	int textureAccess;
	SDL_QueryTexture(texture, nullptr, &textureAccess, nullptr, nullptr);

	return (ContainsBit(textureAccess, queriedAccess));
}

bool ContainsBit(int target, int query)
{
	return ((target & query) != 0);
}
