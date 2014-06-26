#pragma once
#include "Tools.h"
#include "Renderer_Wrapper.h"
#include <string>
#include <list>

/*
The ToolKit contains global variables and functions.
*/

extern Window* g_window;
extern Renderer* g_renderer;
extern SDL_Event event;

// Short Convenience
SDL_Rect RectFromXY(const Coordinates& pos, const Dimensions& dims);

template <class T>
bool listContains(const std::list<T>& lst, const T& target)
{
	for (auto element : lst)
		if (element == target) return true;
	return false;
}


// RENDERER DELEGATIONS
	// Initialisation
	inline void InitRendererAndWindow(void) 
		{ g_window = new Window(); g_renderer = new Renderer(g_window); } // Initialise window and renderer
	
	// Texture Creation
	inline SDL_Texture* CreateTexture(SDL_Surface* surface) 
		{ return g_renderer->CreateTexture(surface); }

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

	inline Coordinates ScreenCenter(void)
		{ return GetLogicalSize() / 2; }

	inline SDL_Texture* LoadImageTexture(std::string filename)
		{ return g_renderer->LoadImageTexture(filename); }

	inline void ClearWindow(void) 
		{ g_renderer->Clear(); }

	inline void UpdateWindow(void) 
		{ g_renderer->Update(); }

	// Window delegations
	inline void ToggleFullscreen(void) 
		{ g_window->ToggleFullscreen(); }