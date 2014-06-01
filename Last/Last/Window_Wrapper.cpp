#pragma once
#include "Window_Wrapper.h"
#include "Config.h"
#include "ToolKit.h"

const char* const WINDOW_TITLE = "Last";

Window_Wrapper::Window_Wrapper(void) : inFullscreen(FULL_SCREEN_INITIAL) 
{ 
	// Resolution
	InitResolution();

	// Init m_window
	RedefineWindow(); 

	// Init Window Surface
	EnsureSuccess(
		SDL_GetWindowSurface(m_window));
}

void Window_Wrapper::RedefineWindow(void)
{
	// Set the size and flag based on whether or not the window is in fullscreen
	Dimensions size = inFullscreen? GetResolution() : LOGICAL_SIZE;
	Uint32 flag =	  inFullscreen? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_BORDERLESS;

	m_window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								size.x, size.y, flag);

	EnsureSuccess(m_window);
}

Dimensions Window_Wrapper::GetResolution(void)
{
	return Dimensions(m_displayMode.w, m_displayMode.h);
}

void Window_Wrapper::InitResolution(void)
{
	// Display Mode
	for (int i = 0; i < SDL_GetNumVideoDisplays(); i++) {
		EnsureSuccess(
			SDL_GetCurrentDisplayMode(i, &m_displayMode));
	}
}

void Window_Wrapper::ToggleFullscreen(void)
{
	inFullscreen = !inFullscreen;
	RedefineWindow();
}