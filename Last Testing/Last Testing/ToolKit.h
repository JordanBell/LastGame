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



// RENDERER DELEGATIONS
	// Initialisation
	inline void InitRendererAndWindow(void) 
		{ g_window = new Window(); g_renderer = new Renderer(g_window); } // Initialise window and renderer
	inline void chk(void) 
		{ if ((!g_renderer) || (!g_window)) InitRendererAndWindow(); } // Initialise window and renderer if they are NULL

	// Texture Creation
	inline SDL_Texture* CreateTexture(SDL_Surface* surface) 
		{ chk(); return g_renderer->CreateTexture(surface); }
	inline SDL_Texture* CreateTexture(Dimensions size, int access = SDL_TEXTUREACCESS_STATIC, Uint32 format = SDL_PIXELFORMAT_ARGB8888) 
		{ chk(); return g_renderer->CreateTexture(size, access, format); }
	
	// Actual Rendering
	inline void RenderToTexture(SDL_Texture* source, SDL_Texture* destination, SDL_Rect* srcrect = NULL, SDL_Rect* dstrect = NULL) 
		{ chk(); g_renderer->RenderToTexture(source, destination, srcrect, dstrect); }
	inline void RenderToWindow(SDL_Texture* source, SDL_Rect* srcrect = NULL, SDL_Rect* dstrect = NULL) 
		{ chk(); g_renderer->RenderToWindow(source, srcrect, dstrect); }

	inline void RenderRectToTexture(SDL_Texture* destination, SDL_Rect* rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
		{ chk(); g_renderer->RenderRectToTexture(destination, rect, r,g,b,a); }
	inline void RenderRectToWindow(SDL_Rect* rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
		{ chk(); g_renderer->RenderRectToWindow(rect, r,g,b,a); }

	// Misc
	inline void ClearWindow(void) 
		{ chk(); g_renderer->Clear(); }
	inline void UpdateWindow(void) 
		{ chk(); g_renderer->Update(); }

	// Window delegations
	inline void ToggleFullscreen(void) 
		{ chk(); g_window->ToggleFullscreen(); }