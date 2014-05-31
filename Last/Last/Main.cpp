#include "ToolKit.h"
#include "SDL.h"
#include "Game.h"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) { return 1; }

	// Get the output lubed up
		#pragma warning(suppress: 6031)
	freopen("CON", "wt", stdout);
		#pragma warning(suppress: 6031)
	freopen("CON", "wt", stderr);

	InitRendererAndWindow();
	 
	//Game Running
	g_game = new Game();
	g_game->Run();

	SDL_Quit();

	return 0;
}