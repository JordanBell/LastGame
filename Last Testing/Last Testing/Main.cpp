#include "ToolKit.h"
#include "SDL.h"
//#include "Game.h"
#include "Test.h"

int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) { return 1; }
	// Get the output lubed up
		#pragma warning(suppress: 6031)
	freopen("CON", "wt", stdout);
		#pragma warning(suppress: 6031)
	freopen("CON", "wt", stderr);
	 
	//Game Running
	/*g_game = new Game();
	g_game->run();*/

	SDL_Rect testClip = {32, 0, TILE_SIZE, TILE_SIZE};
	Test test = Test(&testClip);
	test.InitMembers();
	test.Run();

	SDL_Quit();

	return 0;
}