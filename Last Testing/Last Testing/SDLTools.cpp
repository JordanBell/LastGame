#include "SDLTools.h"
#include "SDL.h"
#include <iostream>

void SDLTools::ErrorResponse(void)
{
	printf("%s..\n", SDL_GetError());
	throw std::runtime_error(SDL_GetError());
}

// Invoke Error Response if argument is NULL
void* SDLTools::EnsureSuccess(void* ptr) { 
	printf("%s.\n", SDL_GetError());
	if (!ptr) 
		ErrorResponse(); 
	else return ptr;
}
	
// Invoke Error Response if argument is non-zero
void SDLTools::EnsureSuccess(int indicator) 
{ 
	printf("%s.\n", SDL_GetError());
	if (indicator != 0) 
		ErrorResponse(); 
}