#pragma once
#include "SDL.h"
#include "Texture_Wrapper.h"
#include "Window_Wrapper.h"
#include <list>

class Renderer_Wrapper
{
public:
	Renderer_Wrapper(Window* window, Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	~Renderer_Wrapper(void);
	
	// Texture Creation
	SDL_Texture* CreateTexture(SDL_Surface* surface);
	SDL_Texture* CreateTexture(Dimensions size, 
							   int access = SDL_TEXTUREACCESS_STATIC, 
							   Uint32 format = SDL_PIXELFORMAT_ARGB8888);

	// Logical Size
	void SetLogicalSize(Dimensions size);
	Dimensions GetLogicalSize(void) const;
	
	// Scale
	void SetScale(float scaleX, float scaleY);
	void SetScale(float scale) { SetScale(scale, scale); }

	// Rendering
	void RenderToTexture(SDL_Texture* source, SDL_Texture* destination, SDL_Rect* srcrect = NULL, SDL_Rect* dstrect = NULL);
	void RenderToWindow(SDL_Texture* source, SDL_Rect* srcrect = NULL, SDL_Rect* dstrect = NULL);
	
	void RenderRectToTexture(SDL_Texture* destination, SDL_Rect* rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void RenderRectToWindow(SDL_Rect* rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	// Misc
	void Clear(void);
	void Update(void);
	void AddTarget(TextureTarget* target) { m_textureTargets.push_back(target); }

	// Window delegations
	void ToggleFullscreen(void) { m_window->ToggleFullscreen(); }
	SDL_Surface* GetWindowSurface(void) const { return m_window->GetSurface(); }
	Dimensions GetWindowSize(void) const;

private:
	SDL_Renderer* m_renderer;
	Window*		  m_window;
	std::list<TextureTarget*> m_textureTargets;

	void RenderRectToTarget(SDL_Rect* rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void RenderToTarget(SDL_Texture* target, void (*renderFunction)(void));
	
	// Resets
	void ResetDrawColor(void);
	void ResetTarget(SDL_Texture* resetValue = NULL) { SetTarget(resetValue); }

	// Targetting
	void SetTarget(SDL_Texture* target);
};

typedef Renderer_Wrapper Renderer;