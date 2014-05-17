#ifndef toolkit_h
#define toolkit_h

#include "SDL.h"
#include "SDL_image.h"
#include "Config.h"
#include <string>

extern SDL_Window* g_window;
extern SDL_Surface* g_windowSurface;
extern SDL_Event event;

// Functions
SDL_Surface* load_image(std::string filename);

void toggleScreenFormat();
void exitFullScreen();

void apply_surface(const XY& pos, SDL_Surface* source, SDL_Rect* clip = NULL);
bool SDL_init();
void SDL_deinit();

#endif