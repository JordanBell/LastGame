#include "toolkit.h"
#include "Game.h"
#include <stdexcept>

int main(int argc, char* args[])
{
	if (!SDL_init()) return 1;
	// Get the output lubed up
		#pragma warning(suppress: 6031)
	freopen("CON", "wt", stdout);
		#pragma warning(suppress: 6031)
	freopen("CON", "wt", stderr);
	 
	//Game Running
	g_game = new Game();
	g_game->run();
	
	SDL_deinit();

	return 0;
}