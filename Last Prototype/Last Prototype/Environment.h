#ifndef environment_h
#define environment_h

#include "EntityContainer.h"

class Environment :
	public EntityContainer
{
public:
	Environment(int x, int y);
	~Environment(void);

	void update(int delta) {}
	void render();

private:
	static int const square_size = 32;
	
	SDL_Rect* sprites[ 8 ][ 5 ]; //All of the clip positions
	// Sprite identifiers for certain objects' clips.
	SDL_Rect* floor;
	SDL_Rect* wall;
	SDL_Rect* shiny_block;
};

extern Environment* g_environment;

#endif