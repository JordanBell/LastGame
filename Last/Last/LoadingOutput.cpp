#include "LoadingOutput.h"
#include "ToolKit.h"

int LoadingOutput::s_total = 0;
LoadingScreen* LoadingOutput::s_loadingScreen = nullptr;

void LoadingOutput::Notify(int percentage, char* message)
{
	if (s_loadingScreen)
	{
		// Add up the total
		s_loadingScreen->Add(percentage);

		// Set the message
		s_loadingScreen->SetMessage(message);

		// Clear the window for manual rendering. This is done here, as it is outside the main game loop (loading between states)
		ClearWindow();

		// Render the loading bar
		s_loadingScreen->Render();

		// Update window with new loading screen
		UpdateWindow();
	}
	else throw runtime_error("Must initialise the loading output before notifying it.");
}