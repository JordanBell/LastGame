#pragma once
#include "SDL.h"
#include "Config.h"
#include "SDLTools.h"
using namespace SDLTools;

class Window_Wrapper
{
public:
	Window_Wrapper(void);
	~Window_Wrapper(void) { SDL_DestroyWindow(m_window); }

	// Initialise the window based on the inFullScreen data
	void RedefineWindow(void);

	SDL_Window* GetWindow(void) const { return m_window; }
	SDL_Surface* GetSurface(void) const { return m_surface; }

	void Update(void) { EnsureSuccess( SDL_UpdateWindowSurface(m_window) ); }

	// Toggle fullscreen
	void ToggleFullscreen(void);

	// Exit Fullscreen
	void ExitFullscreen(void) { if (inFullscreen) ToggleFullscreen(); }

private:
	SDL_Window* m_window;
	SDL_Surface* m_surface;
	bool inFullscreen;
};

extern const char* const WINDOW_TITLE;
typedef Window_Wrapper Window;