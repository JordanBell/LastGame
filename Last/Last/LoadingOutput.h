#pragma once
#include <stdio.h>
#include <string>

/*
This class statically handles data sent by different components 
during their loading stages. This will ultimately be used
to notify the user of the progress during the loading screen.
*/
class LoadingOutput
{
public:
	static void Notify(int percentage, char* message = "");

private:
	static int s_total;
};
