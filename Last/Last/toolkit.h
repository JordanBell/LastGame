#pragma once
#include "Tools.h"
#include "Renderer_Wrapper.h"
#include <string>

extern Window* g_window;
extern Renderer* g_renderer;
extern SDL_Event event;

// Short Convenience
SDL_Rect RectFromXY(Coordinates pos, Dimensions dims);

// Check if a given texture has a queried access
bool TextureHasAccess(SDL_Texture* texture, Uint32 queriedAccess);

// Check if a number contains a bit
bool ContainsBit(int target, int query);



// RENDERER DELEGATIONS
	// Initialisation
	inline void InitRendererAndWindow(void) 
		{ g_window = new Window(); g_renderer = new Renderer(g_window); } // Initialise window and renderer
	
	// Texture Creation
	inline SDL_Texture* CreateTexture(Dimensions size, int access = SDL_TEXTUREACCESS_STATIC, Uint32 format = SDL_PIXELFORMAT_ARGB8888) 
		{ return g_renderer->CreateTexture(size, access, format); }
	
	// Actual Rendering
	inline void RenderTextureToTexture(SDL_Texture* source, SDL_Texture* destination, SDL_Rect* srcrect = nullptr, SDL_Rect* dstrect = nullptr) 
		{ g_renderer->RenderToTexture(source, destination, srcrect, dstrect); }
	inline void RenderTextureToWindow(SDL_Texture* source, SDL_Rect* srcrect = nullptr, SDL_Rect* dstrect = nullptr) 
		{ g_renderer->RenderToWindow(source, srcrect, dstrect); }

	inline void RenderRectToTexture(SDL_Texture* destination, SDL_Rect* rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
		{ g_renderer->RenderRectToTexture(destination, rect, r,g,b,a); }
	inline void RenderRectToWindow(SDL_Rect* rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
		{ g_renderer->RenderRectToWindow(rect, r,g,b,a); }

	// Misc
	inline Dimensions GetLogicalSize(void)
		{ return g_renderer->GetLogicalSize(); }
	inline SDL_Texture* LoadImageTexture(std::string filename)
		{ return g_renderer->LoadImageTexture(filename); }
	inline void ClearWindow(void) 
		{ g_renderer->Clear(); }
	inline void UpdateWindow(void) 
		{ g_renderer->Update(); }

	// Window delegations
	inline void ToggleFullscreen(void) 
		{ g_window->ToggleFullscreen(); }