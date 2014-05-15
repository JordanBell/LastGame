/*Some of this source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/

#include "toolkit.h"
#include "Resources.h"
#include <string>

const char* WINDOW_TITLE("Last");
SDL_Surface* screen;
TTF_Font* font;
SDL_Color textColor = { 0, 0, 0 };
SDL_Event event;
bool inFullScreen;

void toggleScreenFormat()
{
	// Get the native screen resolution
	const SDL_VideoInfo* info = SDL_GetVideoInfo();

	// Change the screen width and height variables to the nearest TILE_SIZE multiple of the native res
	//SCREEN_WIDTH = info->current_w;
	//SCREEN_HEIGHT = info->current_h;
	
	screen = inFullScreen ? 
			 SDL_SetVideoMode(WINDOWED_SCREEN_RES.x, WINDOWED_SCREEN_RES.y, SCREEN_BPP, SDL_SWSURFACE) :
			 SDL_SetVideoMode(info->current_w,		 info->current_h,		SCREEN_BPP, SDL_FULLSCREEN);
	inFullScreen = !inFullScreen;
}

void exitFullScreen()
{
	if (inFullScreen) toggleScreenFormat();
}

bool SDL_init()
{
	//Init Subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return false;
    
	//Init Screen
	inFullScreen = !FULL_SCREEN;
	toggleScreenFormat();
	SDL_WM_SetCaption(WINDOW_TITLE, NULL);
	if (screen == NULL) return false;
    
	//Init SDL_ttf
	if (TTF_Init() == -1) return false;
    
	return load_files();
}

void SDL_deinit()
{
	//Free all of this
	delete g_resources;

	//Quit all of that
	TTF_Quit();
	SDL_Quit();
}

bool load_files() //Load files, and check for the success of each one
{
	try {
		g_resources = new Resources();
	}
	catch (std::exception &e) {
		printf(e.what());
		return false;
	}

	return true;
}

SDL_Surface* load_image(std::string filename)
{
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());
	if (loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);

		if (optimizedImage != NULL)
		{
			Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF);
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
		}
	}

	return optimizedImage;
}

<<<<<<< HEAD
void apply_surface(const XY& pos, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
=======
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
{
	if (source != NULL)
	{
			SDL_Rect offset;

<<<<<<< HEAD
		offset.x = pos.x;
		offset.y = pos.y;
=======
		offset.x = x;
		offset.y = y;

>>>>>>> parent of f6a1270... Oh wait, no. Conversion Complete
		SDL_BlitSurface(source, clip, destination, &offset);
	}
}


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

//Flip flags
const int FLIP_VERTICAL = 1;
const int FLIP_HORIZONTAL = 2;

//The surfaces
SDL_Surface *topLeft = NULL;
SDL_Surface *topRight = NULL;
SDL_Surface *bottomLeft = NULL;
SDL_Surface *bottomRight = NULL;

Uint32 get_pixel32( SDL_Surface *surface, int x, int y )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Get the requested pixel
    return pixels[ ( y * surface->w ) + x ];
}

void put_pixel32( SDL_Surface *surface, int x, int y, Uint32 pixel )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Set the pixel
    pixels[ ( y * surface->w ) + x ] = pixel;
}

SDL_Surface *flip_surface( SDL_Surface *surface, int flags )
{
    //Pointer to the soon to be flipped surface
    SDL_Surface *flipped = NULL;

    //If the image is color keyed
    if( surface->flags & SDL_SRCCOLORKEY )
    {
        flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0 );
    }
    //Otherwise
    else
    {
        flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
    }

    //If the surface must be locked
    if( SDL_MUSTLOCK( surface ) )
    {
        //Lock the surface
        SDL_LockSurface( surface );
    }

    //Go through columns
    for( int x = 0, rx = flipped->w - 1; x < flipped->w; x++, rx-- )
    {
        //Go through rows
        for( int y = 0, ry = flipped->h - 1; y < flipped->h; y++, ry-- )
        {
            //Get pixel
            Uint32 pixel = get_pixel32( surface, x, y );

            //Copy pixel
            if( ( flags & FLIP_VERTICAL ) && ( flags & FLIP_HORIZONTAL ) )
            {
                put_pixel32( flipped, rx, ry, pixel );
            }
            else if( flags & FLIP_HORIZONTAL )
            {
                put_pixel32( flipped, rx, y, pixel );
            }
            else if( flags & FLIP_VERTICAL )
            {
                put_pixel32( flipped, x, ry, pixel );
            }
        }
    }

    //Unlock surface
    if( SDL_MUSTLOCK( surface ) )
    {
        SDL_UnlockSurface( surface );
    }

    //Copy color key
    if( surface->flags & SDL_SRCCOLORKEY )
    {
        SDL_SetColorKey( flipped, SDL_RLEACCEL | SDL_SRCCOLORKEY, surface->format->colorkey );
    }

    //Return flipped surface
    return flipped;
}
