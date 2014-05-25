#pragma once
#include "Tools.h"
#include "Renderer_Wrapper.h"
#include <string>

extern Window* g_window;
extern Renderer* g_renderer;
extern SDL_Event event;

bool InitSDL(void);

// Load an image as a surface, from a file
SDL_Surface* LoadImageSurface(std::string filename);

// Short Convenience
SDL_Rect RectFromXY(Coordinates pos, Dimensions dims);