#include "Test.h"
#include "ToolKit.h"

void Test::Run(void)
{
	/*g_window = new Window();
	g_renderer = new Renderer(g_window);*/

	chk();
	g_renderer->SetLogicalSize(Dimensions(16*TILE_SIZE, 10*TILE_SIZE));

	//// Top Left
	//	ClearWindow();
	//testImage.RenderToTarget(Coordinates(0));
	//	UpdateWindow();
	//SDL_Delay(1000);

	//// Top Right
	//	ClearWindow();
	//testImage.RenderToTarget(Coordinates(15*TILE_SIZE, 0));
	//	UpdateWindow();
	//SDL_Delay(1000);

	//// Bottom Left
	//	ClearWindow();
	//testImage.RenderToTarget(Coordinates(0, 9*TILE_SIZE));
	//	UpdateWindow();
	//SDL_Delay(1000);

	//// Bottom Right
	//	ClearWindow();
	//	UpdateWindow();
	//SDL_Delay(1000);

	// Render image to container
	/*testImage.SetStreamer(&testTarget);
	testImage.RenderToTarget(Coordinates(32));*/

	testDuplicate.SetStreamer(&testTarget);
	testDuplicate.RenderToTarget(Coordinates());

	/*for (int i = 0; i < 16; i++)
		for (int j = 0; j < 10; j++)
			testImage.RenderToTarget(Coordinates(i*TILE_SIZE, j*TILE_SIZE));*/

	for (int i = 1; i < 10; i++)
	{
		Coordinates changingPosition = (16*i, 16*i);
		SDL_Rect changingRect = {(i/2)*TILE_SIZE, 0, TILE_SIZE, TILE_SIZE};
		testImage.SetClip(&changingRect);

		// Clear screen
		ClearWindow();

			// Render image to container
			testImage.RenderToTarget(changingPosition);

			/*testImage.RenderToTarget(Coordinates(32));
			testDuplicate.RenderToTarget(Coordinates());*/
			
			// Render container image to screen
			testTarget.RenderToTarget(Dimensions(7.5*TILE_SIZE, 4.5*TILE_SIZE));
			//testTarget.RenderToTarget(Dimensions());
			//g_renderer->SetScale(10-(i*10)/10);

		// Update the renderer
		UpdateWindow();

		SDL_Delay(200);
	}
}

void Test::InitMembers(void)
{
	//
}
