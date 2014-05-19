#ifndef toolkit_h
#define toolkit_h

#include "SDL.h"
#include "SDL_image.h"
#include "Config.h"
#include <string>

extern SDL_Window* g_window;
extern SDL_Surface* g_windowSurface;
extern SDL_Renderer* g_renderer;
extern SDL_DisplayMode* g_displayMode;
extern SDL_Event event;

// Functions
void initDisplayModeInfo();
void defineWindow();
void initRenderer();

SDL_Surface* LoadImageSurface(std::string filename);
SDL_Texture* LoadImageTexture(std::string filename);

// Inline convenience
inline void toggleScreenFormat();
inline void exitFullScreen();

// Applying Images
void RenderSurface(const XY& pos, SDL_Surface* source, SDL_Rect* clip = NULL);
void RenderTexture(const XY& pos, SDL_Texture* source, SDL_Rect* clip = NULL);
//void RenderTexture(SDL_Texture* source, SDL_Rect* clip = NULL, SDL_Rect* targetRect = NULL);
void SurfaceToSurface(const XY& pos, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);

bool SDL_init();
void SDL_deinit();

#endif