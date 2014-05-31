#include "Window_Wrapper.h"
#include "Config.h"

const char* const WINDOW_TITLE = "Last";

Window_Wrapper::Window_Wrapper(void) : inFullscreen(FULL_SCREEN_INITIAL) 
{ 
	// Init m_window
	RedefineWindow(); 

	// Init its surface
	m_surface = SDL_GetWindowSurface(m_window); 
	EnsureSuccess(m_surface); 
}

void Window_Wrapper::RedefineWindow(void)
{
	Dimensions size = inFullscreen? HARD_MONITOR_RES : LOGICAL_SIZE;
	Uint32 flag = inFullscreen? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;

	m_window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								size.x, size.y, flag);
	
	/*m_window = inFullscreen ? 
		SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
						 1680, 
						 1050,
						 SDL_WINDOW_FULLSCREEN) :
		SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
						 16*TILE_SIZE, 
						 10*TILE_SIZE,
						 SDL_WINDOW_SHOWN);*/

	EnsureSuccess(m_window);
}

void Window_Wrapper::ToggleFullscreen(void)
{
	inFullscreen = !inFullscreen;
	RedefineWindow();
}