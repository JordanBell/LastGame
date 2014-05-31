#include "ToolKit.h"
#include "Config.h"
#include "Renderer_Wrapper.h"
#include "SDL.h"
#include "SDL_image.h"

Window* g_window = nullptr;
Renderer* g_renderer = nullptr;

#ifndef RectFromXY
SDL_Rect RectFromXY(const Coordinates& pos, const Dimensions& dims) 
{ 
	SDL_Rect r_rect = {pos.x, pos.y, 
					   dims.x, dims.y}; 
	return r_rect; 
}
#endif