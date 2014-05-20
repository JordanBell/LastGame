#pragma once

#include "SDL.h"
#include "Tools.h"
#include <string>

extern SDL_Window* g_window;
extern SDL_Surface* g_windowSurface;
extern SDL_Renderer* g_renderer;
extern SDL_DisplayMode* g_displayMode;
extern SDL_Event event;

// Functions
void initDisplayModeInfo(void);
void defineWindow(void);
void initRenderer(void);

SDL_Surface* LoadImageSurface(std::string filename);
SDL_Texture* LoadImageTexture(std::string filename);

// Inline convenience
void ToggleScreenFormat(void);
void exitFullScreen(void);

// Applying Images
void RenderSurface(const Coordinates& pos, SDL_Surface* source, SDL_Rect* clip = NULL);
void RenderTexture(const Coordinates& pos, SDL_Texture* source, SDL_Rect* clip = NULL, SDL_Renderer* renderer = g_renderer);
//void RenderTexture(SDL_Texture* source, SDL_Rect* clip = NULL, SDL_Rect* targetRect = NULL);
void SurfaceToSurface(const Coordinates& pos, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);

bool SDL_init(void);
void SDL_deinit(void);