#ifndef toolkit_h
#define toolkit_h

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Config.h"
#include <string>

extern SDL_Surface* screen;
extern SDL_Color textColor;
extern SDL_Event event;

// Functions
SDL_Surface* load_image(std::string filename);

void toggleScreenFormat();
void exitFullScreen();

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);
bool SDL_init();
bool load_files();
void SDL_deinit();

#endif