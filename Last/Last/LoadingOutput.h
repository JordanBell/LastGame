#pragma once
#include <stdio.h>
#include <string>
#include "LoadingScreen.h"

/*
This class statically handles data sent by different components 
during their loading stages. This will ultimately be used
to notify the user of the progress during the loading screen.
*/
class LoadingOutput
{
public:
	// Initialise the static loading bar
	static void Initialise(void) { s_loadingScreen = new LoadingScreen(); }
	// Delete the static loading bar
	static void Uninitialise(void) { delete s_loadingScreen; }

	// Update the static loading bar
	static void Notify(int percentage, char* message = "");

private:
	static int s_total;
	static LoadingScreen* s_loadingScreen;
};
