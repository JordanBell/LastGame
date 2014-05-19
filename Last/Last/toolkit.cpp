/*Some of this source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

#include "toolkit.h"
#include "Resources.h"
#include <string>

const char* WINDOW_TITLE("Last");
SDL_Window* g_window;
SDL_Renderer* g_renderer;
SDL_Surface* g_windowSurface;
SDL_DisplayMode* g_displayMode;
SDL_Event event;
bool inFullScreen;

void initDisplayModeInfo()
{
	// Get current display mode of all displays.
	for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i)
	{
		int errorIndicator = SDL_GetCurrentDisplayMode(i, g_displayMode);

		if (errorIndicator != 0) {
			printf("Could not get display mode for video display #%d: %s", i, SDL_GetError());
		}
	}
}

void defineWindow()
{
	g_window = inFullScreen ? 
		SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
						 HARD_MONITOR_RES.x, 
						 HARD_MONITOR_RES.y,
						 SDL_WINDOW_FULLSCREEN_DESKTOP) :
		SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
						 WINDOWED_SCREEN_RES.x, 
						 WINDOWED_SCREEN_RES.y,
						 SDL_WINDOW_SHOWN);
}

void initRenderer()
{
	// Set up the renderer and window with this information
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Set some rendering info
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(g_renderer, WINDOWED_SCREEN_RES.x, WINDOWED_SCREEN_RES.y);
}

inline void toggleScreenFormat()
{
	// Toggle
	inFullScreen = !inFullScreen;
	
	// Redefine
	defineWindow();
}

inline void exitFullScreen() { if (inFullScreen) toggleScreenFormat(); }

bool SDL_init()
{
	//Init Subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;
    
	//Init Screen bool
	inFullScreen = FULL_SCREEN_INITIAL;

	// Display info
	initDisplayModeInfo();
	// Window
	defineWindow();
	// Window renderer
	initRenderer();

	// If initialisation was successful, get the window's surface
	if ((g_displayMode == NULL) ||
		(g_window == NULL)		||
		(g_renderer == NULL))	return false;
	else g_windowSurface = SDL_GetWindowSurface(g_window);
    
	return true;
}

void SDL_deinit()
{
	//Quit all of that
	SDL_Quit();
}

SDL_Texture* LoadImage(std::string filename)
{
	SDL_Texture* r_texture;

	SDL_Surface* loadedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());
	if (loadedImage == NULL) {
		printf("Unable to load image: %s\n", filename.c_str());
	}
	else
	{
		r_texture = SDL_CreateTextureFromSurface(g_renderer, loadedImage);

		if (r_texture == NULL) {
			printf("Unable to create texture for loaded image %s\n", filename.c_str());
		}

		SDL_FreeSurface(loadedImage);
	}

	return r_texture;
}

// !!!!!!!!!!!!!!!!!!!!!!!!! Changed XY to Directions for pos, as this will highlight wherever I've used this
void RenderSurface(const XY& pos, SDL_Surface* source, SDL_Rect* clip)
{
	if (source != NULL)
	{
		SDL_Rect offset = {0,0,0,0};

		/*offset.x = pos.x;
		offset.y = pos.y;*/
		SDL_BlitSurface(source, clip, g_windowSurface, &offset);
	}
}

void RenderTexture(SDL_Texture* source, SDL_Rect* clip, const XY& pos)
{
	if (source != NULL)
	{
		// Create rect for pos
		SDL_Rect wholeScreenArea = {(int)pos.x, (int)pos.y, clip->w, clip->h};

		// Render
		SDL_RenderCopy(g_renderer, source, clip, &wholeScreenArea);
	}
}

//void RenderTexture(SDL_Texture* source, SDL_Rect* clip, SDL_Rect* targetRect)
//{
//	if (source != NULL)
//	{
//		// Render
//		SDL_RenderCopy(g_renderer, source, clip, targetRect);
//	}
//}