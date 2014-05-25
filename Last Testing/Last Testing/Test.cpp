#include "Test.h"
#include "ToolKit.h"

void Test::Run(void)
{
	/*g_window = new Window();
	g_renderer = new Renderer(g_window);*/

	chk();

	for (int i = 1; i < 10; i++)
	{
		Coordinates changingPosition = (5*i, 5*i);

		//Clear screen
		ClearWindow();
		//SDL_RenderClear(renderer);

			//// Render image to container
			//testImage.RenderToTarget(Coordinates(32, 32));
			
			SDL_Rect testRect = {25, 25, 100, 100};
			RenderRectToWindow(&testRect, 0xFF, 0xFF, 0xFF, 0xFF);

			//// Render container image to screen
			//testStreamer.RenderToTarget(Coordinates(0));

		// Update the renderer
		UpdateWindow();
		//SDL_UpdateWindowSurface(window);
		//SDL_RenderPresent(renderer);

		SDL_Delay(200);
	}
}

void Test::InitMembers(void)
{
	//testImage.SetStreamer(&testStreamer);
}
