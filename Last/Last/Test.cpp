#include "Test.h"
#include "ToolKit.h"

void Test::Run(void)
{
	for (int i = 1; i < 10; i++)
	{
		Coordinates changingPosition = (5*i, 5*i);

		//Clear screen
		g_renderer.Clear();

			//// Render image to container
			//testImage.RenderToTarget(Coordinates(32, 32));
			
			SDL_Rect testRect = {25, 25, 100, 100};
			g_renderer.RenderRectToWindow(&testRect, 0xFF, 0xFF, 0xFF, 0xFF);

			//// Render container image to screen
			//testStreamer.RenderToTarget(Coordinates(0));

		// Update the renderer
		g_renderer.Update();

		SDL_Delay(200);
	}
}

void Test::InitMembers(void)
{
	//testImage.SetStreamer(&testStreamer);
}
