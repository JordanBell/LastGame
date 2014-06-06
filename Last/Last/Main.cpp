#include "ToolKit.h"
#include "SDL.h"
#include "GameStateManager.h"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) return 1;
    if (TTF_Init()					  == -1) return 1;

	// Get the output lubed up
		#pragma warning(suppress: 6031)
	freopen("CON", "wt", stdout);
		#pragma warning(suppress: 6031)
	freopen("CON", "wt", stderr);

	InitRendererAndWindow();

	//Game Running
	g_manager = new GameStateManager();
	g_manager->Run();

	SDL_Quit();

	return 0;
}