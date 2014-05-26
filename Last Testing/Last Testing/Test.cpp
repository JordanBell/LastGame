#include "Test.h"
#include "ToolKit.h"

void Test::Run(void)
{
	/*g_window = new Window();
	g_renderer = new Renderer(g_window);*/

	chk();
	g_renderer->SetLogicalSize(Dimensions(16*TILE_SIZE, 10*TILE_SIZE));

	// Top Left
		ClearWindow();
	testImage.RenderToTarget(Coordinates(0));
		UpdateWindow();
	SDL_Delay(1000);

	// Top Right
		ClearWindow();
	testImage.RenderToTarget(Coordinates(15*TILE_SIZE, 0));
		UpdateWindow();
	SDL_Delay(1000);

	// Bottom Left
		ClearWindow();
	testImage.RenderToTarget(Coordinates(0, 9*TILE_SIZE));
		UpdateWindow();
	SDL_Delay(1000);

	// Bottom Right
		ClearWindow();
	testImage.RenderToTarget(Coordinates(15*TILE_SIZE, 9*TILE_SIZE));
		UpdateWindow();
	SDL_Delay(1000);

	for (int i = 1; i < 10; i++)
	{
		Coordinates changingPosition = (5*i, 5*i);
		SDL_Rect changingRect = {(i/2)*TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
		//testImage.SetClip(&changingRect);

		//Clear screen
		ClearWindow();

			// Render image to container
			testImage.RenderToTarget(changingPosition);
			
			// Render container image to screen
			//testTarget.RenderToTarget(Coordinates(0));

		// Update the renderer
		UpdateWindow();

		SDL_Delay(200);
	}
}

void Test::InitMembers(void)
{
	//testImage.SetStreamer(&testTarget);
}
