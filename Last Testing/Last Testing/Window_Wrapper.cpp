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
	// NOTE: WINDOWED_SCREEN_RES has not yet initialised, so must be hard-coded in.
	Dimensions size = inFullscreen? Dimensions() : Dimensions(16*TILE_SIZE, 10*TILE_SIZE);
	Uint32 flags = inFullscreen? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;

	/*m_window = SDL_CreateWindow(WINDOW_TITLE, 
								SDL_WINDOWPOS_UNDEFINED, 
								SDL_WINDOWPOS_UNDEFINED,
								size.x, size.y,
								flags);*/

	m_window = inFullscreen ? 
		SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
						 1680, 
						 1050,
						 SDL_WINDOW_FULLSCREEN) :
		SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
						 16*TILE_SIZE, 
						 10*TILE_SIZE,
						 SDL_WINDOW_SHOWN);

	EnsureSuccess(m_window);
}

void Window_Wrapper::ToggleFullscreen(void)
{
	inFullscreen = !inFullscreen;
	RedefineWindow();
}




/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

/*//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gHelloWorld = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gHelloWorld = SDL_LoadBMP( "02_getting_an_image_on_the_screen/hello_world.bmp" );
	if( gHelloWorld == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface( gHelloWorld );
	gHelloWorld = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Apply the image
			SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );
			
			//Update the surface
			SDL_UpdateWindowSurface( gWindow );

			//Wait two seconds
			SDL_Delay( 2000 );
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}*/