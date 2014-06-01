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

	// Define (or redefine) the window based on the inFullScreen value
	void RedefineWindow(void);

	// Get the SDL_Window that this object wraps around
	SDL_Window* GetWindow(void) const { return m_window; }

	Dimensions GetResolution(void);

	// Update the window's surface
	void Update(void) { EnsureSuccess( SDL_UpdateWindowSurface(m_window) ); }

	// Toggle fullscreen
	void ToggleFullscreen(void);

	// Exit Fullscreen
	void ExitFullscreen(void) { if (inFullscreen) ToggleFullscreen(); }

private:
	SDL_DisplayMode m_displayMode;
	SDL_Window* m_window; // The SDL_Window that this object wraps around
	bool inFullscreen; // Whether or not the window should be in full screen mode

	void InitResolution(void);
};

extern const char* const WINDOW_TITLE;
typedef Window_Wrapper Window;